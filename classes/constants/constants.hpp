#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

class Constants {
    const static std::array< int, 6 > candies;
public:

    static enum components{RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, NONE, ALL, EMPTY, WALL, 

                            RED_STRIPED_BOMB, BLUE_STRIPED_BOMB, GREEN_STRIPED_BOMB, YELLOW_STRIPED_BOMB,
                            PURPLE_STRIPED_BOMB, ORANGE_STRIPED_BOMB,

                            RED_WRAPPED_BOMB, BLUE_WRAPPED_BOMB, GREEN_WRAPPED_BOMB, YELLOW_WRAPPED_BOMB,
                            PURPLE_WRAPPED_BOMB, ORANGE_WRAPPED_BOMB,

                            SPECIAL_BOMB} components;

    static const int VERTICAL = 0;
    static const int HORIZONTAL = 1;

    static const int BELOW_LEFT = 0;
    static const int BELOW = 1;
    static const int BELOW_RIGHT = 2;

    static int randomCandy() {return candies[rand() % 6];}
};



#endif