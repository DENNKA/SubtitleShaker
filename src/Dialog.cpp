#include "Dialog.h"

Dialog::Dialog(std::wstring type, std::wstring dialog){
    const auto& temp = operation.split(dialog, ',');
    format.reserve(temp.size() + 1);
    format.push_back(type);
    format.insert(format.end(), temp.begin(), temp.end());
    if (format.size() == 10){
        format.push_back(L"");
    } else
    for (int i = format.size(); i > 11; i--){
        format[format.size() - 2] += L"," + format.back();
        format.pop_back();
    }
}

std::wstring Dialog::getString(){return operation.uniteStrings(format, ',', true);}

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

void Dialog::insert(int pos, std::wstring text){
    format[Text].insert(pos, text);
}

void Dialog::addTextInBegin(std::wstring text){
    format[Text].insert(0, text);
}

void Dialog::addTextInEnd(std::wstring text){
    format[Text].insert(format[Text].size(), text);
}

void Dialog::addAssTag(const std::wstring& tag, const std::vector<int> numbers, int pos){
    std::vector<std::wstring> numbersString;
    numbersString.reserve(numbers.size());
    for (auto it : numbers){
        numbersString.push_back(std::to_wstring(it));
    }
    addAssTag(tag, numbersString, pos);
}

void Dialog::addAssTag(const std::wstring& tag, const std::vector<int> numbers, const std::wstring& textArg, int pos){
    std::vector<std::wstring> numbersString;
    numbersString.reserve(numbers.size() + 1);
    for (auto it : numbers){
        numbersString.push_back(std::to_wstring(it));
    }
    numbersString.push_back(textArg);
    addAssTag(tag, numbersString, pos);
}

void Dialog::addAssTag(const std::wstring& tag, const std::vector<std::wstring> numbers, int pos){
    std::wstring left = L"", right = L"";
    if (numbers.size() > 1){
        left = L"(";
        right = L")";
    }
    insert(pos, L"{\\"+ tag + left + operation.uniteStrings(numbers, L',', false) + right + L"}");
}

std::pair<int, std::vector<std::wstring>> Dialog::parseAssTag(const std::wstring& tag, bool erase){
    std::vector<std::wstring> numbers;
    auto& text = format[Text];
    std::size_t tagPosition = text.find(tag);
    if (tagPosition == std::wstring::npos) return std::make_pair(1, numbers);
    std::size_t tagStart = text.find(L"(", tagPosition);
    if (tagStart == std::wstring::npos) return std::make_pair(1, numbers);
    std::size_t tagEnd = text.find(L")", tagStart);
    if (tagEnd == std::wstring::npos) return std::make_pair(1, numbers);
    std::wstring textNumbers(text, tagStart + 1, tagEnd - tagStart - 1);
    if (erase){
        text.erase(tagPosition, tagEnd);
    }
    //erase spaces
    textNumbers.erase(remove_if(textNumbers.begin(), textNumbers.end(), isspace), textNumbers.end());
    numbers = operation.split(textNumbers, ',');
    return std::make_pair(0, numbers);
}

Dialog::~Dialog()
{
    //dtor
}
