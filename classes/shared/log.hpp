#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>


class Log {

    struct ctorKey {
        explicit ctorKey(int) {};
    };

    static std::unique_ptr<Log> singleton;

    int eventCounter = 0;
    std::vector<std::string> vecView;
    std::vector<std::string> vecModel;

    //std::ofstream logfile; 
    // Log: logfile{"logs.txt"} {};
    Log(){};


public:
    
    explicit Log(ctorKey) : Log() {}

    static Log &get();

    void addViewMessage(const std::string &message);
    void addModelMessage(const std::string &message);

    void Dump();

    void addMove() {};

    ~Log() {Dump();}
};



#endif