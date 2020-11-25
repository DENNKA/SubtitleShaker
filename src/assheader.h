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
        void setHeader(std::vector<std::wstring>& header, std::wstring version);
        const std::vector<std::wstring>& getHeader();
        virtual ~ASSHeader();
        std::vector<std::wstring> format;
        enum Format{
            PlayResX,
            PlayResY,

            FormatEnd
        };
    protected:

    private:
        Operation operation;
        std::vector<std::wstring> header;
        std::wstring versionText = L"Version: ";
        std::wstring linkText = L"Link: github.com/DENNKA/SubtitleShaker.git";
};

#endif // ASSHEADER_H
