#include "Operation.h"

Operation::Operation()
{
    //ctor
}

std::vector<std::wstring> Operation::split(std::wstring str, const wchar_t delim){
    std::vector<std::wstring> elems;
    std::wstringstream ss(str);
    std::wstring item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::wstring Operation::uniteStrings(std::vector<std::wstring> str, const char delim, bool firstAndSecondNoDelim){
    std::wstring out;
    for (uint i = 0; i < str.size(); i++){
        out += str[i];
        if (i != str.size() - 1 && !(i == 0 && firstAndSecondNoDelim)){
            out += delim;
        }
    }
    return out;
}

int Operation::getMsFromString(const std::wstring& str){
    auto timeVector = getTimeVector(str);
    int ms = 0;
    std::vector<int> time;
    for (auto& it : timeVector){
        time.push_back(std::stoi(it));
    }
    ms = ((((time[0] * 60) + time[1]) * 60) + time[2]) * 1000 + time[3] * 10;
    return ms;
}

std::wstring Operation::getTimeStringFromMs(int ms){
    int centiseconds = ms % 1000 / 10;
    ms /= 1000;
    int seconds = ms % 60;
    ms /= 60;
    int minutes = ms % 60;
    int hours = ms / 60;

    std::vector<std::wstring> vec;
    vec.push_back(std::to_wstring(hours));
    vec.push_back(std::to_wstring(minutes));
    vec.push_back(std::to_wstring(seconds));
    vec.push_back(std::to_wstring(centiseconds));
    for (uint i = 1; i < vec.size(); i++){
        if (vec[i].length() == 1){
            vec[i].insert(vec[i].begin(), '0');
        }
    }
    return vec[0] + L':' + vec[1] + L':' + vec[2] + L'.' + vec[3];
}

Operation::~Operation()
{
    //dtor
}

std::vector<std::wstring> Operation::getTimeVector(const std::wstring& str){
    auto time = split(str, ':');
    auto temp = split(time[2], '.');
    time.pop_back();
    time.push_back(temp[0]);
    time.push_back(temp[1]);
    return time;
}
