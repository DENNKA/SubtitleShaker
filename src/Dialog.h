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
        Dialog(std::string type, std::string style);
        std::string getString();
        std::vector<std::string> format;
        void setStartMs(int ms);
        void setEndMs(int ms);
        int getStartMs();
        int getEndMs();
        void addTextInBegin(std::string text);
        void addTextInEnd(std::string text);
        void addAssTag(const std::string& tag, const std::vector<int> numbers);
        void addAssTag(const std::string& tag, const std::vector<std::string> numbers);
        std::pair<int, std::vector<std::string>> parseAssTag(const std::string& tag, bool erase = false);
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
