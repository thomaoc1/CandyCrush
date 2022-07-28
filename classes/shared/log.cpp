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
void Log::addViewMessage(const std::string &message) {
    vecView.push_back(message);
    //logfile<<message<<std::endl;
}

void Log::addModelMessage(const std::string &message) {
    vecModel.push_back(message);
    //logfile<<message<<std::endl;
}

void addModelMatrix(std::vector<std::vector<Cell>>&){
    
}

std::unique_ptr<Log> Log::singleton;
