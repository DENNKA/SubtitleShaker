#ifndef DIALOG_H
#define DIALOG_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Operation.h"

class Dialog
{
    public:
        Dialog(std::wstring type, std::wstring style);
        std::wstring getString();
        std::vector<std::wstring> format;
        void setStartMs(int ms);
        void setEndMs(int ms);
        int getStartMs();
        int getEndMs();
        void addTextInBegin(std::wstring text);
        void addTextInEnd(std::wstring text);
        void addAssTag(const std::wstring& tag, const std::vector<int> numbers);
        void addAssTag(const std::wstring& tag, const std::vector<std::wstring> numbers);
        std::pair<int, std::vector<std::wstring>> parseAssTag(const std::wstring& tag, bool erase = false);
        enum Format{
            Type,
            Layer,
            Start,
            End,
            Style,
            Name,
            MarginL,
            MarginR,
            MarginV,
            Effect,
            Text,

            FormatEnd
        };
        virtual ~Dialog();
    protected:

    private:
        Operation operation;
};

#endif // DIALOG_H
