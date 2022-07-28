#include "log.hpp"


/**
 * @brief
 * 
 * @return Log &
 * 
 */
Log &Log::get() {
    if (!singleton) singleton = std::make_unique<Log>(ctorKey{0});
    return *singleton;
}


/**
 * @brief
 * 
 * @param message
 * 
 */
void Log::addMessage(const std::string &message) {
    //logfile<<message<<std::endl;
    ++eventCounter;
}

void addMatrix(int vecNum, std::vector<std::vector<int>>){
    
}

std::unique_ptr<Log> Log::singleton;
