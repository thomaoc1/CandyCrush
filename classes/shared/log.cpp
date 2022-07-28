#include "log.hpp"


/**
 * @brief
 * 
 * @return Log &
 * 
 */
Log &Log::get() {
    if (!singleton){ singleton=std::unique_ptr<Log>(new Log());}
    return *singleton;
}


/**
 * @brief
 * 
 * @param message
 * 
 */
void Log::addMessage(const std::string &message) {
    logfile<<message<<std::endl;
    ++eventCounter;
}

std::unique_ptr<Log> Log::singleton;
