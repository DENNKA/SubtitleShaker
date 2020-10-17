#include "Operation.h"

Operation::Operation()
{
    //ctor
}

std::vector<std::string> Operation::split(std::string str, const char delim){
    std::vector<std::string> elems;
    std::stringstream ss(str);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::string Operation::uniteStrings(std::vector<std::string> str, const char delim, bool firstAndSecondNoDelim){
    std::string out;
    for (int i = 0; i < str.size(); i++){
        out += str[i];
        if (i != str.size() - 1 && !(i == 0 && firstAndSecondNoDelim)){
            out += delim;
        }
    }
    return out;
}

int Operation::getMsFromString(const std::string& str){
    auto timeVector = getTimeVector(str);
    int ms = 0;
    std::vector<int> time;
    for (auto& it : timeVector){
        time.push_back(std::stoi(it));
    }
    ms = ((((time[0] * 60) + time[1]) * 60) + time[2]) * 1000 + time[3] * 10;
    return ms;
}

std::string Operation::getTimeStringFromMs(int ms){
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

Operation::~Operation()
{
    //dtor
}

std::vector<std::string> Operation::getTimeVector(const std::string& str){
    auto time = split(str, ':');
    auto temp = split(time[2], '.');
    time.pop_back();
    time.push_back(temp[0]);
    time.push_back(temp[1]);
    return time;
}
