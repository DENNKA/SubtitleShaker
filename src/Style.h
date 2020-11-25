#ifndef STYLE_H
#define STYLE_H

#include <vector>
#include <string>
#include <iostream>

#include "Operation.h"
#include "ASSInfo.h"

class Style
{
    public:
        Style(std::wstring type, std::wstring style);
        std::wstring getString();
        std::pair<int, int> calculatePosition(int playResX, int playResY, bool customMargin = false, int marginL = 0, int marginR = 0, int marginV = 0);
        virtual ~Style();

    protected:

    private:
        Operation operation;
        std::vector<std::wstring> format;
        enum Format{
            Type,
            Name,
            Fontname,
            Fontsize,
            PrimaryColour,
            SecondaryColour,
            OutlineColour,
            BackColour,
            Bold,
            Italic,
            Underline,
            StrikeOut,
            ScaleX,
            ScaleY,
            Spacing,
            Angle,
            BorderStyle,
            Outline,
            Shadow,
            Alignment,
            MarginL,
            MarginR,
            MarginV,
            Encoding,

            FormatEnd
        };
};

#endif // STYLE_H
