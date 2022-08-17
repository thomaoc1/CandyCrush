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
#include <iostream>
#include <string>

class FileHandler {
    const int randomCandy = -1;
    GameData gameData;
    std::vector<Point> candies, walls, frostings, cherries;
    std::vector<Point> hazels, wrapped, striped, special;
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
    int numOfInterpreter(int index, const std::string &line) const;
    void objectivesInterpreter(const std::string &line);
};

#endif