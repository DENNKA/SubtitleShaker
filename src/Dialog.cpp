#include "Dialog.h"

Dialog::Dialog(std::string type, std::string dialog){
    const auto& temp = operation.split(dialog, ',');
    format.reserve(temp.size() + 1);
    format.push_back(type);
    format.insert(format.end(), temp.begin(), temp.end());
    if (format.size() == 10){
        format.push_back("");
    } else
    for (int i = format.size(); i > 11; i--){
        format[format.size() - 2] += "," + format.back();
        format.pop_back();
    }
}

std::string Dialog::getString(){return operation.uniteStrings(format, ',', true);}

void Dialog::setStartMs(int ms){
    format[Start] = operation.getTimeStringFromMs(ms);
}

void Dialog::setEndMs(int ms){
    format[End] = operation.getTimeStringFromMs(ms);
}

int Dialog::getStartMs(){
    return operation.getMsFromString(format[Start]);
}

int Dialog::getEndMs(){
    return operation.getMsFromString(format[End]);
}

void Dialog::addTextInBegin(std::string text){
    format[Text].insert(0, text);
}

void Dialog::addTextInEnd(std::string text){
    format[Text].insert(format[Text].size(), text);
}

void Dialog::addAssTag(const std::string& tag, const std::vector<int> numbers){
    std::vector<std::string> numbersString;
    numbersString.reserve(numbers.size());
    for (auto it : numbers){
        numbersString.push_back(std::to_string(it));
    }
    addAssTag(tag, numbersString);
}

void Dialog::addAssTag(const std::string& tag, const std::vector<std::string> numbers){
    addTextInBegin("{\\"+ tag + "(" + operation.uniteStrings(numbers, ',', false) + ")}");
}

Dialog::~Dialog()
{
    //dtor
}
