#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

class Constants {
    const static std::array< int, 6 > candies;
public:

    /* Model Constants */
    static enum directions{VERTICAL, HORIZONTAL, } directions;
    static enum below{BELOW, BELOW_LEFT, BELOW_RIGHT} below;

    /* View Constants */
    static const double FPS;
    static const double WINDOW_HEIGHT;
    static const double WINDOW_WIDTH;
    static const double GAME_WINDOW_Y;
    static const double GAME_WINDOW_X;
    static const double INTER_CELL;
    static const double CELL_SIZE;


    static enum components{RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, NONE, ALL, EMPTY, WALL, 

                            RED_STRIPED_BOMB, BLUE_STRIPED_BOMB, GREEN_STRIPED_BOMB, YELLOW_STRIPED_BOMB,
                            PURPLE_STRIPED_BOMB, ORANGE_STRIPED_BOMB,

                            RED_WRAPPED_BOMB, BLUE_WRAPPED_BOMB, GREEN_WRAPPED_BOMB, YELLOW_WRAPPED_BOMB,
                            PURPLE_WRAPPED_BOMB, ORANGE_WRAPPED_BOMB,

                            SPECIAL_BOMB} components;

    
    static int randomCandy() {return candies[rand() % 6];}
};



#endif