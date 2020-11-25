#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Operation
{
    public:
        Operation();
        std::vector<std::wstring> split(std::wstring str, const wchar_t delim);
        std::wstring uniteStrings(std::vector<std::wstring> str, const char delim, bool firstAndSecondNoDelim = false);
        int getMsFromString(const std::wstring& str);
        std::wstring getTimeStringFromMs(int ms);
        virtual ~Operation();

    protected:

    private:
        std::vector<std::wstring> getTimeVector(const std::wstring& str);
};

#endif // OPERATION_H
