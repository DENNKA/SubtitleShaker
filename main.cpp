#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <map>
#include <iomanip>

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

void help(){
    #define out(x) std::cout<<x<<std::endl;
    #define out2(shortOption, option, description) std::cout<<std::setw(4)<<shortOption<<std::setw(16)<<option<<"   "<<description<<std::endl;

    std::cout<<"0 - English"<<std::endl;
    std::cout<<"1 - Russian"<<std::endl;
    int language;
    std::cin>>language;
    //--settings_file
    if (language == 0){
        out("==============================================================")
        out("subtitleShaker [options]")
        out2("-h", "--help", "Help")
        out2("-i", "--input", "Input file")
        out2("-o", "--output", "Output file")
        out2("-sf", "--settings_file", "Settings file")
        out2("-s", "--seed", "Seed for random")
        out("==============================================================")
        out("Option in settings file:")
        out2("-s", "--shake", "Shake every n ms")
        out2("-i", "--intensity", "Intensity in pixels")
        out2("-ix", "--intensity_x", "Intensity in pixels at x")
        out2("-iy", "--intensity_y", "Intensity in pixels at y")
        out2("-q", "--quiet", "Quiet mode")
        out("==============================================================")
    }
    if (language == 1){
        out("==============================================================")
        out("subtitleShaker [опции]")
        out2("-h", "--help", "Помощь")
        out2("-i", "--input", "Исходный файл")
        out2("-o", "--output", "Файл для вывода")
        out2("-sf", "--settings_file", "Файл настроек")
        out2("-s", "--seed", "Семя для генерации случайных чисел")
        out("==============================================================")
        out("Опции в файле настроек:")
        out2("-s", "--shake", "Трясти каждые n миллисекунд")
        out2("-i", "--intensity", "Интенсивность в пикселях")
        out2("-ix", "--intensity_x", "Интенсивность в пикселях по x")
        out2("-iy", "--intensity_y", "Интенсивность в пикселях по y")
        out2("-q", "--quiet", "Тихий режим")
        out("==============================================================")
    }
    #undef out
}

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "rus");
    std::string fileIn = "in.ass";
    std::string fileOut = "out.ass";
    std::string str;
    std::string strFind;
    std::string compareStr = "Dialogue:";
    std::string settingsFile = "settings.txt";
    int dialogueCounter = 0;

    int dialogueNumber = 0;
    int intensityx = 0;
    int intensityy = 0;
    int shakeEveryMs = 0;
    bool quiet = false;
    unsigned int seed = 0;
    bool customSeed = false;
    for (int i = 1; i < argc; i++){
        #define it (std::string)argv[i]
        if (it == "-sf" || it == "--settings_file"){
            settingsFile = argv[i + 1];
        } else
        if (it == "-o" || it == "--output"){
            fileOut = argv[i + 1];
        } else
        if (it == "-i" || it == "--input"){
            fileIn = argv[i + 1];
        } else
        if (it == "-s" || it == "--seed"){
            seed = std::stoll(argv[i + 1]);
            customSeed = true;
        }
        if (it == "-h" || it == "--help"){
            help();
            return 0;
        }
        #undef it
    }

    if (!customSeed) seed = time(NULL);
    srand(seed);

    std::vector<int> needToProcess;
    std::map<int, std::vector<int>> settings;
    enum Settings{
        DialogueNumber,
        ShakeEveryMs,
        Intensityx,
        Intensityy,
        Quiet,

        End
    };
    std::ifstream fin;
    fin.open(settingsFile);
    if(!fin.is_open()) {std::cout<<"Settings file not found, abort"<<std::endl; return 1;}
    while(getline(fin, str)){
        auto elems = split(str, ' ');
        std::string needFind("-");
        if (elems.size() == 0) continue;
        int start, end;
        if (elems[0][0] == '-'){
            auto pos = split(str, '-');
            if (pos.size() == 2){
                auto it = std::find(needToProcess.begin(), needToProcess.end(), std::stoi(pos[1]));
                if (it != needToProcess.end()){
                    needToProcess.erase(it);
                    settings.erase(std::stoi(pos[1]));
                } else std::cout<<"Syntax error, ignoring. "<<"Missing to delete: "<<std::stoi(pos[1])<<std::endl;
            }
            else
            if (pos.size() == 3){
                for (int i = std::stoi(pos[1]); i <= std::stoi(pos[2]); i++){
                    auto it = std::find(needToProcess.begin(), needToProcess.end(), i);
                    if (it != needToProcess.end()){
                        needToProcess.erase(it);
                        settings.erase(i);
                    } else std::cout<<"Syntax error, ignoring. "<<"Missing to delete: "<<i<<std::endl;
                }
            }
            else std::cout<<"Syntax error, ignoring: "<<"\"-\""<<std::endl;
            continue;
        }
        if (elems[0].find(needFind) != std::string::npos){
            auto pos = split(elems[0], '-');
            start = std::stoi(pos[0]);
            end = std::stoi(pos[1]);
        }
        else{
            start = std::stoi(elems[0]);
            end = start;
        }
        for (int i = start; i <= end; i++){
            needToProcess.push_back(i);
            settings[i].resize(End);
            for (int j = 0; j < elems.size(); j++){
                #define it (std::string)elems[j]
                if (it == "-i" || it == "--intensity"){
                    settings[i][Intensityx] = std::stoi(elems[j + 1]);
                    settings[i][Intensityy] = std::stoi(elems[j + 1]);
                } else
                if (it == "-ix" || it == "--intensity_x"){
                    settings[i][Intensityx] = std::stoi(elems[j + 1]);
                } else
                if (it == "-iy" || it == "--intensity_y"){
                    settings[i][Intensityy] = std::stoi(elems[j + 1]);
                } else
                if (it == "-s" || it == "--shake"){
                    settings[i][ShakeEveryMs] = std::stoi(elems[j + 1]);
                } else
                if (it == "-q" || it == "--quiet"){
                    settings[i][Quiet] = true;
                }
                #undef it
            }
        }
    }
    std::sort(needToProcess.begin(), needToProcess.end());
    needToProcess.erase(unique(needToProcess.begin(), needToProcess.end()), needToProcess.end());
    fin.close();
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
    {
        std::ofstream fout(fileOut);
        std::ifstream fin(fileIn);
        if(!fin.is_open()) {std::cout<<"File not found, abort"<<std::endl; return 1;}
        if(!fout.is_open()) return 1;
        while(getline(fin, str)){
            fout<<str<<std::endl;
        }
    }

    /*std::vector<std::string> file;
    {
        std::ifstream fin(fileIn);
        if(!fin.is_open()) {std::cout<<"File not found, abort"<<std::endl; return 1;}
        while(getline(fin, str)){
            file.push_back(str);
        }
    }*/

    std::string tempFile = "temp.ass";

    for (auto it = needToProcess.rbegin(); it != needToProcess.rend(); ++it){
        dialogueCounter = 0;

        fin.open(fileOut);
        if(!fin.is_open()) {std::cout<<"File not found, abort"<<std::endl; return 1;}
        std::ofstream fout(tempFile);
        if(!fout.is_open()) return 1;
        while(getline(fin, str)){
            fout<<str<<std::endl;
        }
        fin.close();
        fout.close();

        fin.open(tempFile);
        if(!fin.is_open()) {std::cout<<"File not found, abort"<<std::endl; return 1;}
        fout.open(fileOut);
        if(!fout.is_open()) return 1;

        auto& settingsi = settings[*it];
        intensityx = settingsi[Intensityx] * 2; // !
        intensityy = settingsi[Intensityy] * 2; // !
        shakeEveryMs = settingsi[ShakeEveryMs];
        if (shakeEveryMs == 0) {std::cout<<"Error: -s can't be zero"<<std::endl; return 1;}
        dialogueNumber = *it;
        quiet = settingsi[Quiet];

        if (!quiet){
            std::cout<<"file "<<"Файл "<<fileIn<<std::endl;
            std::cout<<"-d Dialogue number "<<"Номер диалога "<<dialogueNumber<<std::endl;
            std::cout<<"-s Shake every n ms "<<"Трясти каждые n миллисекунд "<<shakeEveryMs<<std::endl;
            std::cout<<"-i Intensity in pixels "<<"Интенсивность в пикселях "<<"x= "<<intensityx/2<<" y= "<<intensityy/2<<std::endl;
            std::cout<<"-q Quiet "<<""<<(quiet ? "true" : "false")<<std::endl;
        }

        std::string compareStyle = "Style:";
        std::string comparePlayResX = "PlayResX:";
        std::string comparePlayResY = "PlayResY:";
        int playResX = 0;
        int playResY = 0;
        std::map<std::string, std::vector<std::string>> styles;

        while(getline(fin, strFind)){
            str = strFind;
            if (strFind.compare(0, 9, comparePlayResX) == 0){
                auto elems = split(strFind, ' ');
                playResX = std::stoi(elems[1]);
            }
            if (strFind.compare(0, 9, comparePlayResY) == 0){
                auto elems = split(strFind, ' ');
                playResY = std::stoi(elems[1]);
            }
            if (strFind.compare(0, 6, compareStyle) == 0){
                auto elems = split(strFind, ',');
                auto elems0 = split(elems[0], ' ');
                styles[elems0[1]].swap(elems);
            }
            if (strFind.compare(0, 9, compareStr) == 0){
                dialogueCounter++;
                if (dialogueCounter == dialogueNumber){
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
                    bool posAdded = false;

                    while (!findPos){ //find or calculate position
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
                                        char buffer[20] = {};
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
                            if (posAdded || playResX == 0 || playResY == 0) {std::cout<<"Error can't calculate position"<<std::endl; return 1;}
                            posAdded = 1;
                            int aligment = std::stoi(styles.at(elems[3]).at(18));
                            int marginL = std::stoi(styles.at(elems[3]).at(19));
                            int marginR = std::stoi(styles.at(elems[3]).at(20));
                            int marginV = std::stoi(styles.at(elems[3]).at(21));

                            int x = 0, y = 0;

                            if (aligment % 3 == 1){ //left
                                x = 0 + marginL;
                            }
                            if (aligment % 3 == 2){ //center
                                x = playResX / 2 + marginL / 2 - marginR / 2;
                            }
                            if (aligment % 3 == 0){ //right
                                x = playResX - marginR;
                            }
                            if (aligment >= 0 && aligment <= 3){ //bottom
                                y = playResY - marginV;
                            }
                            if (aligment >= 4 && aligment <= 6){ //mid
                                y = playResY / 2;
                            }
                            if (aligment >= 7 && aligment <= 9){ //top
                                y = 0 + marginV;
                            }
                            for (int i = 0, commaCounter = 0; i < str.length(); i++){
                                if (str[i] == ','){
                                    commaCounter++;
                                    if (commaCounter == 9){
                                        strFind.insert(i + 1, (std::string)"{\\pos(" + std::to_string(x) + ',' + std::to_string(y) + ")}");
                                        str = strFind;
                                    }
                                }
                            }
                        }
                    }

                    std::string newStartString;
                    std::string newEndString;
                    int counter = 0;
                    while (newMsStart + shakeEveryMs < msEnd || counter == 0){
                        counter++;
                        str = strFind;

                        newMsEnd = newMsStart + shakeEveryMs;
                        newStartString = getTimeStringFromMs(newMsStart);
                        newEndString = getTimeStringFromMs(newMsEnd);
                        str.replace(posStart, elems[1].length(), newStartString);
                        str.replace(posEnd, elems[2].length(), newEndString);
                        newMsStart += shakeEveryMs;

                        int newPosx = intensityx == 0 ? posx : posx + rand() % intensityx - intensityx / 2;
                        int newPosy = intensityy == 0 ? posy : posy + rand() % intensityy - intensityy / 2;
                        //str.replace(posxString, posVec[0].length(), std::to_string(newPosx));
                        //str.replace(posyString, posVec[1].length(), std::to_string(newPosy));

                        int posyDigits = 1;
                        auto tempPosy = posy;
                        while ((tempPosy /= 10) > 0) posyDigits++;
                        int posxDigits = 1;
                        auto tempPosx = posx;
                        while ((tempPosx /= 10) > 0) posxDigits++;

                        str.erase(posyString, posyDigits);
                        str.erase(posxString, posxDigits);
                        auto stringPosX = std::to_string(newPosx);
                        auto stringPosY = std::to_string(newPosy);
                        int shifty = 0;
                        if (posVec[0].length() > stringPosX.length()){
                            shifty = -1;
                        }
                        str.insert(posxString, stringPosX);
                        str.insert(posyString + shifty, stringPosY);

                        fout<<str<<std::endl;
                    }
                    str.replace(posStart, elems[1].length(), newEndString);
                    newEndString = getTimeStringFromMs(msEnd);
                    str.replace(posEnd, elems[2].length(), newEndString);

                    int newPosx = intensityx == 0 ? posx : posx + rand() % intensityx - intensityx / 2; //copy paste lol (need delete this)
                    int newPosy = intensityy == 0 ? posy : posy + rand() % intensityy - intensityy / 2;
                    //str.replace(posxString, posVec[0].length(), std::to_string(newPosx));
                    //str.replace(posyString, posVec[1].length(), std::to_string(newPosy));

                    int posyDigits = 1;
                    auto tempPosy = posy;
                    while ((tempPosy /= 10) > 0) posyDigits++;
                    int posxDigits = 1;
                    auto tempPosx = posx;
                    while ((tempPosx /= 10) > 0) posxDigits++;

                    str.erase(posyString, posyDigits);
                    str.erase(posxString, posxDigits);
                    auto stringPosX = std::to_string(newPosx);
                    auto stringPosY = std::to_string(newPosy);
                    int shifty = 0;
                    if (posVec[0].length() > stringPosX.length()){
                        shifty = -1;
                    }
                    str.insert(posxString, stringPosX);
                    str.insert(posyString + shifty, stringPosY);

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
        fin.close();
        fout.close();
    }

    if (remove(tempFile.c_str()) != 0) std::cout<<"Can't delete temp file, ignoring"<<std::endl;

    return 0;
}
