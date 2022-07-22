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

#include <fstream>
#include <string>

class FileHandler {
    GameData gameData;
public:
    FileHandler(const std::string &filename);
    GameData getGameData() const {return gameData;}
private:
    Point lineInterpreter(const std::string &filename) const;
};

#endif