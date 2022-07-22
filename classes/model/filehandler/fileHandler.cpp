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
Point FileHandler::lineInterpreter(const std::string &line) const {
    return {((int)line[2] - 48), ((int)line[0] - 48)};
}


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


FileHandler::FileHandler(const std::string &filename) {
    std::ifstream inFile(filename);
    std::string line;
    
    int numWalls, numFrostings;
    std::vector<Point> walls, frostings;

    if (!inFile.is_open()) {
        std::cout << "Failed to open" << std::endl;
        exit(1);
    } 

    getline(inFile, line, '\n'); 
    numWalls = stoi(line);

    for (int i = 0; i < numWalls; ++i) {
        getline(inFile, line, '\n');
        walls.push_back(lineInterpreter(line));
    }

    getline(inFile, line, '\n'); 
    numFrostings = stoi(line);    

    for (int i = 0; i < numWalls; ++i) {
        getline(inFile, line, '\n');
        frostings.push_back(lineInterpreter(line));
    }

    gameData.walls = walls;
    gameData.frostings = frostings;
}