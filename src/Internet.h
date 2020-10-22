#ifndef INTERNET_H
#define INTERNET_H

#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "iostream"

class Internet{
    public:
        std::string get(const std::string& host, const std::string& target);
    private:

};

#endif //INTERNET_H
