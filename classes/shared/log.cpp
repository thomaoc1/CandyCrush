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
    //std::cout<<"pushed back"<<std::endl;
    //std::cout << message << std::endl;
    //logfile<<message<<std::endl;
}

void Log::addModelMessage(const std::string &message) {
    vecModel.push_back(message);
    // std::cout << message << std::endl;
    //logfile<<message<<std::endl;
}

    

void Log::Dump(){
    

    std::fstream ViewLog;
    ViewLog.open("logs/ViewLog.txt",std::ios_base::out);
 
    for(int i = 0; i < static_cast<int>(vecView.size()); i++)
    {
        ViewLog << vecView[i] << std::endl;
    }
    ViewLog.close();
    
    std::fstream ModelLog;
    ModelLog.open("logs/ModelLog.txt",std::ios_base::out);
    for(int i = 0; i < static_cast<int>(vecModel.size()); i++)
    {
        ModelLog << vecModel[i] << std::endl;
    }
    ModelLog.close();

}

std::unique_ptr<Log> Log::singleton;
