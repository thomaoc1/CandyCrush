#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

class Constants {
    static const std::array< std::string, 6 > candies;
public:
    static const std::string RED;
    static const std::string BLUE;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string PURPLE;
    static const std::string ORANGE;
    static const std::string NONE;
    static const std::string ALL;

    static const std::string WALL;
    static const std::string BOMB;
    static const std::string STRIPED;
    static const std::string WRAPPED;


    static const std::string EMPTY;

    static const int VERTICAL = 0;
    static const int HORIZONTAL = 1;

    static const int BELOW_LEFT = 0;
    static const int BELOW = 1;
    static const int BELOW_RIGHT = 2;

    static const std::string randomCandy() {return candies[rand() % 6];}
};



#endif