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
        SubtitleShaker(int argc, char *argv[]);
        int start();
        int tryFindFiles();
        void help();
        int parseSettings();
        int readFile(const std::string& fileName, std::vector<std::string>& file);  // "file" it is output
        int writeFile(const std::string& fileName, const std::vector<std::string>& file);
        int loadSubtitleFileInfo();
        int loadSettings(std::string fileName);
        int startProccesing();
        virtual ~SubtitleShaker();

    protected:

    private:
        const std::string version = "2.0.0";
        int parseArg(std::vector<std::string> argv);
        Operation operation;
        ASSHeader assHeader;
        Translator translator;
        bool verbose = false;
        std::vector<std::string> argv;
        std::string settingsFile;
        std::string fileOut;
        std::string fileOutPrefix = "MOD_";
        std::string fileIn;
        std::vector<std::string> file;
        std::map<std::string, Style> styles;
        std::vector<Style> stylesVector;
        std::vector<Dialog> dialogues;
        bool inputFileLoaded = false;

        //vector of pair int (number string) and vector strings (settingsToProcess), vector with settings have size settingsToProcess::End
        std::vector<int> needToProcess;
        std::map<int, std::vector<std::string>> settings;
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
