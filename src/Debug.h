#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <experimental/filesystem> //wstring_convert, i don't know why

#if (__linux || __unix || __posix)
    #define OS_LINUX 1
#elif (_WIN64 || _WIN32)
    #define OS_WINDOWS 1
#else
    #define OS_UNKNOWN 1
#endif

#ifdef OS_LINUX
    //#include <locale.h>
#elif OS_WINDOWS
    #include <windows.h>
#endif

enum class Lang : int{
    en,
    ru
};

class Debug{
    public:
        Debug();
        void out(Lang lang, std::wstring msg);
        template <typename T>
        void out(T msg){output(std::wcout, msg);}
        template <class T>
        void exception(T e){std::wcerr << "Error: " << e.what() << std::endl;}
        void error(Lang lang, std::wstring msg);
        template <typename T>
        void error(T msg){output(std::wcerr, msg);}
        Lang getLang();
    private:
        Lang lang = Lang::en;
        void output(std::wostream& out, Lang lang, std::wstring msg);
        void output(std::wostream& out, std::string msg);
};

static Debug debug;

#endif //DEBUG_H
