#include "fileHandler.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                      Private Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Converts line into coordinates
 * 
 * @param line
 * 
 * @return Point
 * 
 */
void FileHandler::asciiGridInterpreter(const std::string &line) {
    for (int i = 0; i < static_cast<int>(line.length()); i += 3) {
        switch (((int)line[i] * 10 - 48) + ((int)line[i] - 48)) {
            case Constants::ANY:
                break;
        }
    }
}


int FileHandler::numOfInterpreter(const std::string &line) const {
    int ret = 0;
    if (line.size() == 1) ret = (int)line[0] - 48;
    else {
        ret = ((int)line[0] - 48) * 10;
        ret += (int)line[1] - 48;
    }
    return ret;
}


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


FileHandler::FileHandler(const std::string &filename) {
    std::ifstream inFile(filename);
    std::string line;

    if (!inFile.is_open()) {
        std::cout << "Failed to open" << std::endl;
        exit(1);
    } 

    getline(inFile, line, '\n');
    gameData.maxSwaps = numOfInterpreter(line);

    getline(inFile, line, '\n');
    int numObjectives;
    numObjectives = numOfInterpreter(line);
    
    
    for (int i = 0; i < numObjectives; ++i ) {
        getline(inFile, line, '\n');
        gameData.objTypes[(int)line[0] - 48] = true;
        gameData.objectives[(int)line[0] - 48] = ((int)line[2] - 48) * 10 + (int)line[3] - 48;
    }

    for (int i = 0; i < 9; ++i) {
        getline(inFile, line, '\n');
        for (int i = 0; i < 9; ++i) {
            asciiGridInterpreter(line);
        }
    }

    gameData.walls = walls;
    gameData.frostings = frostings;
}