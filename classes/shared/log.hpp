#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "../model/containers/cell.hpp"

class Log {

    struct ctorKey {
        explicit ctorKey(int) {};
    };

    static std::unique_ptr<Log> singleton;

    int eventCounter = 0;
    std::vector<std::string> vec1;
    std::vector<std::string> vec2;
    //std::ofstream logfile; 
    // Log: logfile{"logs.txt"} {};
    Log(){};


public:
    
    explicit Log(ctorKey) : Log() {}

    static Log &get();

    void addMessage(const std::string &message);
    void addMatrix() {};
    void addMove() {};
};



#endif