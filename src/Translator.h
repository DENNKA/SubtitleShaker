#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <codecvt>

#include "Internet.h"
#include "Operation.h"

#include <iomanip>

class Translator{
    public:
        Translator();
        void setLang(std::wstring languageFrom = L"", std::wstring languageTo = L"");
        std::wstring translate(std::wstring str);
    private:
        Internet internet;
        Operation operation;
        std::string urlencode(std::string s);
        std::map<std::string, std::wstring> dictUtf;  // first utf code \u1000 second it's letter wchar_t
        std::wstring languageFrom, languageTo;
};

#endif //TRANSLATOR_H
