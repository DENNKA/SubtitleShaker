#ifndef SUBTITLESHAKER_H
#define SUBTITLESHAKER_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#include <exception>
#include <experimental/filesystem>

#include "assheader.h"
#include "Style.h"
#include "Dialog.h"
#include "Debug.h"
#include "Translator.h"

class SubtitleShaker
{
    public:
        SubtitleShaker();
        void tryFindFiles();
        void help();
        void parseSettings(int argc, char *argv[]);
        void parseSettings(std::vector<std::wstring> argv);
        void readFile(const std::wstring& fileName, std::vector<std::wstring>& file);  // "file" it is output
        void writeFile(const std::wstring& fileName, const std::vector<std::wstring>& file);
        void loadSubtitleFileInfo();
        void loadSettings(std::wstring fileName);
        void startProccesing();
        virtual ~SubtitleShaker();

    protected:

    private:
        #define SS_MACROS_TO_STRING_2(x) #x
        #define SS_MACROS_TO_STRING(x) SS_MACROS_TO_STRING_2(x)
        const std::string version = SS_MACROS_TO_STRING(GIT_VERSION);
        void parseArg(std::vector<std::wstring> argv);
        Operation operation;
        ASSHeader assHeader;
        Translator translator;
        bool verbose = false;
        std::wstring settingsFile;
        std::wstring fileOut;
        std::wstring fileOutPrefix = L"MOD_";
        std::wstring fileIn;
        std::vector<std::wstring> file;
        std::map<std::wstring, Style> styles;
        std::vector<Style> stylesVector;
        std::vector<Dialog> dialogues;
        bool inputFileLoaded = false;

        //vector of pair int (number string) and vector strings (settingsToProcess), vector with settings have size settingsToProcess::End
        std::vector<int> needToProcess;
        std::map<int, std::vector<std::wstring>> settings;
        enum settingsToProcess{
            Time,
            IntensityX,
            IntensityY,
            Verbose,    //not used
            //new settings add here
            FirstMode,
            //mode settings (like "-f", "2")
            //new mode slot and etc
            End
        };
};

#endif // SUBTITLESHAKER_H
