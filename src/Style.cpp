#include "Style.h"

Style::Style(std::string type, std::string style){
    const auto& temp = operation.split(style, ',');
    format.reserve(temp.size() + 1);
    format.push_back(type);
    format.insert(format.end(), temp.begin(), temp.end());
}

std::string Style::getString(){return operation.uniteStrings(format, ',', true);}

std::pair<int, int> Style::calculatePosition(int playResX, int playResY, bool customMargin, int marginL, int marginR, int marginV){
    if (!customMargin){
        marginL = std::stoi(format[MarginL]);
        marginR = std::stoi(format[MarginR]);
        marginV = std::stoi(format[MarginV]);
    }
    int aligment = std::stoi(format[Alignment]);
    //calc
    int x = 0, y = 0;

    if (aligment % 3 == 1){ //left
        x = 0 + marginL;
    }
    if (aligment % 3 == 2){ //center
        x = playResX / 2 + marginL / 2 - marginR / 2;
    }
    if (aligment % 3 == 0){ //right
        x = playResX - marginR;
    }
    if (aligment >= 0 && aligment <= 3){ //bottom
        y = playResY - marginV;
    }
    if (aligment >= 4 && aligment <= 6){ //mid
        y = playResY / 2;
    }
    if (aligment >= 7 && aligment <= 9){ //top
        y = 0 + marginV;
    }
    return std::make_pair(x, y);
}

Style::~Style()
{
    //dtor
}
