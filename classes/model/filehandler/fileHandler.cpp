#include "fileHandler.hpp"
#include <cmath>

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


void FileHandler::interpretFile(const std::string &filename) {
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
        int objType = numOfInterpreter(0, line);
        gameData.objTypes[objType] = true;
        gameData.objectives[objType] = numOfInterpreter(3, line);
        if (objType == Constants::POPS) gameData.colour = numOfInterpreter(6, line);
    }

    for (int i = 0; i < 9; ++i) {
        getline(inFile, line, '\n');
        asciiGridInterpreter(i, line);
    }
}


int FileHandler::getBestScore() const {
    std::ifstream inFile("db/bestscore/bestscore.txt");
    std::string line;

    if (!inFile.is_open()) {
        std::cout << "Failed to open" << std::endl;
        exit(1);
    } 

    getline(inFile, line, '\n');

    int savedScore = 0;
    for (int i = 0; i < static_cast<int>(line.length()); ++i) 
        savedScore += static_cast<int>(((int)line[i] - 48) * pow(10, static_cast<int>(line.length()) - 1 - i));

    return savedScore;
}


void FileHandler::dumpScore(int score) const {
    int savedScore = getBestScore();    
    if (score <= savedScore) return;
    std::ofstream outFile("db/bestscore/bestscore.txt");
    outFile << std::to_string(score) << "\n";
}


void FileHandler::resetScore() const {
    std::ofstream outFile("db/bestscore/bestscore.txt");
    outFile << std::to_string(0) << "\n";
}