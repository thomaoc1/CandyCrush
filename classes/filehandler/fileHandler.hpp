/**
 * @file filhandler.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Handles the opening and interpreting of text files.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "gameData.hpp"
#include "../common/constants.hpp"

#include <fstream>
#include <iostream>
#include <string>

class FileHandler {
    GameData gameData;
public:
    FileHandler(const std::string &filename) {interpretFile(filename);}
    FileHandler()=default;

    void interpretFile(const std::string &filename);
    void setFile(const std::string &filename) {interpretFile(filename);}
    GameData getGameData() const {return gameData;}
    void dumpScore(int score) const;
    void resetScore() const;
    int getBestScore() const;
private:
    void asciiGridInterpreter(int row, const std::string &line);
    ComponentType componentInterpreter(int index, const std::string &line) const;
    int numOfInterpreter(int index, const std::string &line) const;
};

#endif