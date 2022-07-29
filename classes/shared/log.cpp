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
<<<<<<< HEAD
void Log::addViewMessage(const std::string &message) {
    vecView.push_back(message);
    //std::cout<<"pushed back"<<std::endl;
    //std::cout << message << std::endl;
=======
void Log::addMessage(const std::string &/*message*/) {
>>>>>>> main
    //logfile<<message<<std::endl;
}

<<<<<<< HEAD
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
        if (i > 0) ViewLog << "================= FRAME " + std::to_string(i) + " =================\n\n";
        ViewLog << vecView[i] << std::endl;
    }
    ViewLog.close();
=======
void addMatrix(int, std::vector<std::vector<int>>){
>>>>>>> main
    
    std::fstream ModelLog;
    ModelLog.open("logs/ModelLog.txt",std::ios_base::out);
    for(int i = 0; i < static_cast<int>(vecModel.size()); i++)
    {
        if (i > 0) ModelLog << "================= FRAME " + std::to_string(i) + " =================\n\n";
        ModelLog << vecModel[i] << std::endl;
    }
    ModelLog.close();

}

std::unique_ptr<Log> Log::singleton;
