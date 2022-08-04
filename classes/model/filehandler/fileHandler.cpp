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
void FileHandler::asciiGridInterpreter(int row, const std::string &line) {
    int col = 0;
    for (int i = 0; i < static_cast<int>(line.length()); i += 3) {
        switch (numOfInterpreter(i, line)) {
            case Constants::RED_WRAPPED_BOMB:
                gameData.wrapped.emplace_back(Point{col, row});
                break;
            case Constants::CHERRY:
                gameData.cherries.emplace_back(Point{col, row});
                break;
            case Constants::FROSTING2:
                gameData.frostings.emplace_back(Point{col, row});
                break;
            case Constants::WALL:
                gameData.walls.emplace_back(Point{col, row});
                break;
            case Constants::ANY:
                break;
        }
        ++col;
    }
}


int FileHandler::numOfInterpreter(int index, const std::string &line) const {
    int ret = 0;
    ret = ((int)line[index] - 48) * 10;
    ret += (int)line[index + 1] - 48;
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
    gameData.maxSwaps = numOfInterpreter(0, line);

    getline(inFile, line, '\n');
    int numObjectives;
    numObjectives = numOfInterpreter(0, line);   
    
    for (int i = 0; i < numObjectives; ++i ) {
        getline(inFile, line, '\n');
        gameData.objTypes[numOfInterpreter(0, line)] = true;
        gameData.objectives[numOfInterpreter(0, line)] = numOfInterpreter(2, line);
    }

    for (int i = 0; i < 9; ++i) {
        getline(inFile, line, '\n');
        asciiGridInterpreter(i, line);
    }
}