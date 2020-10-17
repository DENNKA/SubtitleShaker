#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#define DEBUG
#define d(x) std::cout<<#x<<" = "<<x<<std::endl;
#define m(x) std::cout<<x<<std::endl;

class Operation
{
    public:
        Operation();
        std::vector<std::string> split(std::string str, const char delim);
        std::string uniteStrings(std::vector<std::string> str, const char delim, bool firstAndSecondNoDelim = false);
        int getMsFromString(const std::string& str);
        std::string getTimeStringFromMs(int ms);
        virtual ~Operation();

    protected:

    private:
        std::vector<std::string> getTimeVector(const std::string& str);
};

#endif // OPERATION_H
