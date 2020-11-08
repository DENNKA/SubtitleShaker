#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <codecvt>

#include "Internet.h"
#include "Operation.h"

class Translator{
    public:
        Translator();
        void setLang(std::string languageFrom = "", std::string languageTo = "");
        std::wstring translate(std::string str);
    private:
        Internet internet;
        Operation operation;
        void hexchar(unsigned char c, unsigned char &hex1, unsigned char &hex2);
        std::string urlencode(std::string s);
        std::map<std::string, std::wstring> dictUtf;  // first utf code \u1000 second it's letter wchar_t
        std::string languageFrom, languageTo;
};

#endif //TRANSLATOR_H
