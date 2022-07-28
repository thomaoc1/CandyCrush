#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <memory>

class Log {

    struct ctorKey {
        explicit ctorKey(int) {};
    };

    static std::unique_ptr<Log> singleton;

    int eventCounter = 0;
    std::ofstream logfile; 
    Log() : logfile{"logs.txt"} {};

public:
    
    explicit Log(ctorKey) : Log() {}

    static Log &get();

    void addMessage(const std::string &message);
    void addMatrix() {};
    void addMove() {};
};



#endif