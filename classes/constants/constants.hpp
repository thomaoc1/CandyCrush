#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

class Constants {
    static const std::string RED;
    static const std::string BLUE;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string PURPLE;
    static const std::string ORANGE;

    static const std::string WALL;
    static const std::string BOMB;

    static const std::array< std::string, 6 > candies;
public:

    static const std::string getRED() {return RED;}
    static const std::string getBLUE() {return BLUE;}
    static const std::string getGREEN() {return GREEN;}
    static const std::string getYELLOW() {return YELLOW;}
    static const std::string getPURPLE() {return PURPLE;}
    static const std::string getORANGE() {return ORANGE;}

    static const std::string randomCandy() {return candies[rand() % 6];}

    static const std::string getWALL() {return WALL;}
    static const std::string getBOMB() {return BOMB;}
};



#endif