/**
 * File : 
 *  fileHandler.hpp
 *
 * Decription :
 *  Extracts data from text files for game levels
 * 
 * Dependencies :
 *  gameData.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */


#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "gameData.hpp"
#include "../../constants/constants.hpp"

#include <fstream>
#include <string>

class FileHandler {
    const int randomCandy = -1;
    GameData gameData;
    std::vector<Point> candies, walls, frostings, cherries;
    std::vector<Point> hazels, wrapped, striped, special;
public:
    FileHandler(const std::string &filename);
    GameData getGameData() const {return gameData;}
private:
    void asciiGridInterpreter(const std::string &line);
    int numOfInterpreter(const std::string &line) const;
    void objectivesInterpreter(const std::string &line);
};

#endif