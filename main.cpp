#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
//using namespace std;

#define DEBUG
#define d(x) std::cout<<#x<<" = "<<x<<std::endl;
#define m(x) std::cout<<x<<std::endl;

std::vector<std::string> split(std::string str, const char delim){
    std::vector<std::string> elems;
    std::stringstream ss(str);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> getTimeVector(std::string str){
    auto time = split(str, ':');
    auto temp = split(time[2], '.');
    time.pop_back();
    time.push_back(temp[0]);
    time.push_back(temp[1]);
    return time;
}

int getMs(std::vector<std::string> timeVector){
    int ms = 0;
    std::vector<int> time;
    for (auto& it : timeVector){
        time.push_back(std::stoi(it));
    }
    ms = ((((time[0] * 60) + time[1]) * 60) + time[2]) * 1000 + time[3] * 10;
    return ms;
}

std::string getTimeStringFromMs(int ms){
    int centiseconds = ms % 1000 / 10;
    ms /= 1000;
    int seconds = ms % 60;
    ms /= 60;
    int minutes = ms % 60;
    int hours = ms / 60;

    std::vector<std::string> vec;
    vec.push_back(std::to_string(hours));
    vec.push_back(std::to_string(minutes));
    vec.push_back(std::to_string(seconds));
    vec.push_back(std::to_string(centiseconds));
    for (int i = 1; i < vec.size(); i++){
        if (vec[i].length() == 1){
            vec[i].insert(vec[i].begin(), '0');
        }
    }
    return vec[0] + ':' + vec[1] + ':' + vec[2] + '.' + vec[3];
}

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "rus");
    std::string file;
    std::string fileOut = "out.ass";
    std::string str;
    std::string strFind;
    std::string compareStr = "Dialogue:";
    int dialogueCounter = 0;

    int dialogueNumber = 0;
    int intensity = 0;
    int shakeEveryMs = 0;
    bool quiet = false;
    for (int i = 1; i < argc; i++){
        if ((std::string)argv[i] == "-i"){
            intensity = std::stoi(argv[i + 1]);
        } else
        if ((std::string)argv[i] == "-s"){
            shakeEveryMs = std::stoi(argv[i + 1]);
        } else
        if ((std::string)argv[i] == "-d"){
            dialogueNumber = std::stoi(argv[i + 1]);
        } else
        if ((std::string)argv[i] == "-q"){
            quiet = true;
        } else
        file = argv[1];
    }
    std::cout<<"file "<<"Файл "<<file<<std::endl;
    std::cout<<"-d Dialogue number "<<"Номер диалога "<<dialogueNumber<<std::endl;
    std::cout<<"-s Shake every n ms "<<"Трясти каждые n миллисекунд "<<shakeEveryMs<<std::endl;
    std::cout<<"-i Intensity in pixels "<<"Интенсивность в пикселях "<<intensity<<std::endl;
    std::cout<<"-q Quiet "<<""<<(quiet ? "true" : "false")<<std::endl;


    /*switch (argc){
        case 5:
            file = argv[1];
            dialogueNumber = std::stoi(argv[2]);
            shakeEveryMs = std::stoi(argv[3]);
            intensity = std::stoi(argv[4]);
            break;
        default:
            std::cout<<"subtitleShaker pathToAssFile dialogueNumber shakeEveryMs intensity";
            return 0;
    }*/
    std::ifstream fin(file);
    if(!fin.is_open()) {std::cout<<"File not found, abort"<<std::endl; return 1;}
    std::ofstream fout(fileOut);
    if(!fout.is_open()) return 1;

    while(getline(fin, strFind)){
        if (strFind.compare(0, 9, compareStr) == 0){
            dialogueCounter++;
            if (dialogueCounter == dialogueNumber){
                str = strFind;
                auto elems = split(str, ',');
                auto timeStart = getTimeVector(elems[1]);
                auto timeEnd = getTimeVector(elems[2]);
                int msStart = getMs(timeStart);
                int msEnd = getMs(timeEnd);
                int newMsStart = msStart;
                int newMsEnd = msEnd;

                shakeEveryMs -= shakeEveryMs % 10;

                //int posStart = str.find(elems[1]);
                //int posEnd = str.find(elems[2]);
                int posStart;
                int posEnd;
                for (int i = 0, pos = 0; i < str.length(); i++){
                    if (str[i] == ','){
                        if (pos++ == 0){
                            posStart = i;
                            posStart++;
                        }
                        else{
                            posEnd = i;
                            posEnd++;
                            break;
                        }
                    }
                }

                int posx, posy;
                int posxString, posyString;
                std::vector<std::string> posVec;

                bool findPos = false;

                for (int i = 0; i + 3 < str.length(); i++){
                    if (str[i] == '\\' && str[i + 1] == 'p' && str[i + 2] == 'o' && str[i + 3] == 's'){
                        for (int j = i; j < str.length(); j++){
                            int start;
                            int end;
                            if (str[j] == '('){
                                start = j;
                                start++;
                                posxString = start;
                                findPos = true;
                            }
                            if (str[j] == ',') posyString = j + 1;
                            if (str[j] == ')'){
                                std::string posString;
                                end = j;
                                char buffer[20];
                                str.copy(buffer, end - start, start);
                                posString = buffer;
                                posVec = split(posString, ',');
                                posx = std::stoi(posVec[0]);
                                posy = std::stoi(posVec[1]);
                                break;
                            }
                        }
                        break;
                    }
                }

                if (!findPos){
                    std::cout<<"Error \\pos not found"<<std::endl;
                    return 1;
                }



                std::string newStartString;
                std::string newEndString;
                while (newMsStart + 100 < msEnd){
                    str = strFind;
                    newMsEnd = newMsStart + shakeEveryMs;
                    newStartString = getTimeStringFromMs(newMsStart);
                    newEndString = getTimeStringFromMs(newMsEnd);
                    str.replace(posStart, elems[1].length(), newStartString);
                    str.replace(posEnd, elems[2].length(), newEndString);
                    newMsStart += shakeEveryMs;

                    int newPosx = posx + rand() % intensity - intensity / 2;
                    int newPosy = posy + rand() % intensity - intensity / 2;
                    //str.replace(posxString, posVec[0].length(), std::to_string(newPosx));
                    //str.replace(posyString, posVec[1].length(), std::to_string(newPosy));
                    str.erase(posyString, posVec[1].length());
                    str.erase(posxString, posVec[0].length());
                    auto stringPosX = std::to_string(newPosx);
                    auto stringPosY = std::to_string(newPosy);
                    int shifty = 0;
                    if (posVec[0].length() > stringPosX.length()){
                        shifty = -1;
                    }
                    str.insert(posxString, stringPosX);
                    str.insert(posyString + shifty, stringPosY);

                    fout<<str<<std::endl;
                    d(newPosx)
                    d(newPosy)
                    d(posVec[0].length())
                    d(stringPosX.length())
                    d(str)
                }
                str.replace(posStart, elems[1].length(), newEndString);
                newEndString = getTimeStringFromMs(msEnd);
                str.replace(posEnd, elems[2].length(), newEndString);
                fout<<str<<std::endl;
            }
            else{
                fout<<str<<std::endl;
            }
        }
        else{
            fout<<str<<std::endl;
        }
    }

    return 0;
}
