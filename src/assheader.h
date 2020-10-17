#ifndef ASSHEADER_H
#define ASSHEADER_H

#include <vector>
#include <string>

#include "Operation.h"
#include "ASSInfo.h"

class ASSHeader
{
    public:
        ASSHeader();
        void setHeader(std::vector<std::string>& header, std::string version);
        const std::vector<std::string>& getHeader();
        virtual ~ASSHeader();
        std::vector<std::string> format;
        enum Format{
            PlayResX,
            PlayResY,

            FormatEnd
        };
    protected:

    private:
        Operation operation;
        std::vector<std::string> header;
};

#endif // ASSHEADER_H
