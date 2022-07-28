#include "log.hpp"



Log& Log::get(){
        if (!singleton){ singleton=std::unique_ptr<Log>(new Log());}
        return *singleton;
    };

void Log::addMessage(const std::string &message){
    logfile<<message<<std::endl;
    ++eventCounter;
};

std::unique_ptr<Log> Log::singleton;
