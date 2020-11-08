#include "Translator.h"

Translator::Translator(){

}

void Translator::setLang(std::string languageFrom, std::string languageTo){
    if (languageFrom != ""){
        this->languageFrom = languageFrom;
    }
    if (languageTo != ""){
        this->languageTo = languageTo;
        #define pushInDict(x,y) dictUtf.insert(std::make_pair(x, L##y))
        if (true/*languageTo == "ru"*/){
            // i didn't find better way
            pushInDict("\\u0454", "є");  // ukrainian
            pushInDict("\\u0456", "і");

            pushInDict("\\u0430","а");  // russian
            pushInDict("\\u0431","б");
            pushInDict("\\u0432","в");
            pushInDict("\\u0433","г");
            pushInDict("\\u0434","д");
            pushInDict("\\u0435","е");
            pushInDict("\\u0451","ё");
            pushInDict("\\u0436","ж");
            pushInDict("\\u0437","з");
            pushInDict("\\u0438","и");
            pushInDict("\\u0439","й");
            pushInDict("\\u043a","к");
            pushInDict("\\u043b","л");
            pushInDict("\\u043c","м");
            pushInDict("\\u043d","н");
            pushInDict("\\u043e","о");
            pushInDict("\\u043f","п");
            pushInDict("\\u0440","р");
            pushInDict("\\u0441","с");
            pushInDict("\\u0442","т");
            pushInDict("\\u0443","у");
            pushInDict("\\u0444","ф");
            pushInDict("\\u0445","х");
            pushInDict("\\u0446","ц");
            pushInDict("\\u0447","ч");
            pushInDict("\\u0448","ш");
            pushInDict("\\u0449","щ");
            pushInDict("\\u044a","ъ");
            pushInDict("\\u044b","ы");
            pushInDict("\\u044c","ь");
            pushInDict("\\u044d","э");
            pushInDict("\\u044e","ю");
            pushInDict("\\u044f","я");
            pushInDict("\\u0410","А");
            pushInDict("\\u0411","Б");
            pushInDict("\\u0412","В");
            pushInDict("\\u0413","Г");
            pushInDict("\\u0414","Д");
            pushInDict("\\u0415","Е");
            pushInDict("\\u0401","Ё");
            pushInDict("\\u0416","Ж");
            pushInDict("\\u0417","З");
            pushInDict("\\u0418","И");
            pushInDict("\\u0419","Й");
            pushInDict("\\u041a","К");
            pushInDict("\\u041b","Л");
            pushInDict("\\u041c","М");
            pushInDict("\\u041d","Н");
            pushInDict("\\u041e","О");
            pushInDict("\\u041f","П");
            pushInDict("\\u0420","Р");
            pushInDict("\\u0421","С");
            pushInDict("\\u0422","Т");
            pushInDict("\\u0423","У");
            pushInDict("\\u0424","Ф");
            pushInDict("\\u0425","Х");
            pushInDict("\\u0426","Ц");
            pushInDict("\\u0427","Ч");
            pushInDict("\\u0428","Ш");
            pushInDict("\\u0429","Щ");
            pushInDict("\\u042a","Ъ");
            pushInDict("\\u042b","Ы");
            pushInDict("\\u042c","Ь");
            pushInDict("\\u042d","Э");
            pushInDict("\\u042e","Ю");
            pushInDict("\\u042f","Я");
        }
    }
}

std::wstring Translator::translate(std::string str){
    //https://mymemory.translated.net/doc/spec.php
    const std::string host = "api.mymemory.translated.net";
    const std::string target = "/get?q=" + urlencode(str) + "&langpair=" + languageFrom + "|" + languageTo;
    auto response = internet.get(host, target);
    std::size_t found = 1;
    std::vector<std::string> translateSamples;
    while (true){
        found = response.find("translatedText", found + 1);
        found = response.find(':', found + 1);
        if (found != std::string::npos){
            std::size_t foundTextBegin = response.find('\"', found + 1);
            std::size_t foundTextEnd = response.find("match", foundTextBegin + 1);
            translateSamples.push_back(std::string(response, foundTextBegin + 1, foundTextEnd - 1));
            found = foundTextEnd;
            break;
        } else break;
    }
    std::string string(translateSamples[0].begin(), translateSamples[0].end() - 37);

    //convert from utf
    std::wstring out;
    for (uint i = 0; i < string.size(); i++){
        if (string.compare(i, 5, "&#39;") == 0){ // for '
            out += '\'';
            i += 4;
        }
        else
        if (string[i] == '\\' && i + 5 < string.size()){
            try{
                out += dictUtf.at(std::string(string.begin() + i, string.begin() + i + 6));
                i += 5;
            }
            catch(...){
                out += (wchar_t)(string[i]);
            }
        }
        else{
            out += (wchar_t)(string[i]);
        }
    }
    return out;
}

void Translator::hexchar(unsigned char c, unsigned char &hex1, unsigned char &hex2){
    hex1 = c / 16;
    hex2 = c % 16;
    hex1 += hex1 <= 9 ? '0' : 'a' - 10;
    hex2 += hex2 <= 9 ? '0' : 'a' - 10;
}

std::string Translator::urlencode(std::string s){
    const char *str = s.c_str();
    std::vector<char> v(s.size());
    v.clear();
    for (std::size_t i = 0, l = s.size(); i < l; i++)
    {
        char c = str[i];
        if ((c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '-' || c == '_' || c == '.' || c == '!' || c == '~' ||
            c == '*' || c == '\'' || c == '(' || c == ')')
        {
            v.push_back(c);
        }
        else if (c == ' ')
        {
            v.push_back('+');
        }
        else
        {
            v.push_back('%');
            unsigned char d1, d2;
            hexchar(c, d1, d2);
            v.push_back(d1);
            v.push_back(d2);
        }
    }

    return std::string(v.cbegin(), v.cend());
}
