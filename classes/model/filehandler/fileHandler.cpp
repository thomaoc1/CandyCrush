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
        using CoordType = std::pair< Point, int >;
        int type = numOfInterpreter(i, line);
        switch (type) {
            case Constants::ANY:
                break;
            default:
                gameData.components.emplace_back(CoordType{Point{col, row}, type});
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