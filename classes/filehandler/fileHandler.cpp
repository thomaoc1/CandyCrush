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
        using CoordType = std::pair< Point, ComponentType >;
        ComponentType component = componentInterpreter(i, line);
        if (component.type != Component::ANY) 
            gameData.components.emplace_back(CoordType{Point{col, row}, component});
        ++col;
    }
}


/**
 * @brief Interprets ASCII representation of a component
 * 
 * @param index 
 * @param line 
 * @return ComponentType 
 */
ComponentType FileHandler::componentInterpreter(int index, const std::string &line) const {
    int colour = (int)line[index] - 48;
    int component = (int)line[index + 1] - 48;
    int test = colour * 10 + component;
    if (static_cast<Component>(test) == Component::ANY) return ComponentType();
    return ComponentType{static_cast<Colour>(colour), static_cast<Component>(component)};
}


/**
 * @brief Interprets numbers
 * 
 * @param index 
 * @param line 
 * @return int 
 */
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


/**
 * @brief Treats text file given.
 * 
 * @param filename 
 */
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
    gameData.objType = static_cast<ObjectiveType>(numOfInterpreter(0, line));;
    gameData.objective = numOfInterpreter(3, line);
    if (gameData.objType == ObjectiveType::POPS) 
        gameData.colour = static_cast<Colour>(numOfInterpreter(6, line));

    for (int i = 0; i < 9; ++i) {
        getline(inFile, line, '\n');
        asciiGridInterpreter(i, line);
    }
}


/**
 * @brief Fetches the best score from the associated textfile.
 * 
 * @return int 
 */
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


/**
 * @brief Dumps the score if it is higher than the bestscore.
 * 
 * @param score 
 */
void FileHandler::dumpScore(int score) const {
    int savedScore = getBestScore();    
    if (score <= savedScore) return;
    std::ofstream outFile("db/bestscore/bestscore.txt");
    outFile << std::to_string(score) << "\n";
}


/**
 * @brief Resets the score.
 * 
 */
void FileHandler::resetScore() const {
    std::ofstream outFile("db/bestscore/bestscore.txt");
    outFile << std::to_string(0) << "\n";
}