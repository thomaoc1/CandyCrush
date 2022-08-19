/**
 * @file enumerations.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Contains all the enumerations used
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP


enum class Colour {
    RED, 
    BLUE, 
    GREEN, 
    YELLOW, 
    PURPLE, 
    ORANGE, 
    BLACK,
    DARK_RED,
    BROWN,
    CYAN,
    NONE
};


enum class Component {
    CANDY,

    STRIPED_BOMB_V, 
    STRIPED_BOMB_H, 

    WRAPPED_BOMB, 

    SPECIAL_BOMB,

    FROSTING1, 
    FROSTING2,
    CHERRY, 
    HAZELNUT,

    WALL, 
    ANY
};


enum class Direction {
    VERTICAL, 
    HORIZONTAL, 
    NO_DIRECTION
};


enum class Beneath {
    LEFT,
    CENTER,
    RIGHT
};


enum class ComponentState {
    POPPED, 
    NOT_POPPED
};


enum class BlastType {
    NO_BLAST, 
    SIMPLE, 
    STRIPED, 
    WRAPPED, 
    SPECIAL
};


enum class AnimPriority {
    IGNORE, 
    CANT_IGNORE
};


enum class AnimationType {
    Pop, 
    Fill, 
    DropDown, 
    DropLeft, 
    DropRight, 
    Swap
};


enum class ObjectiveType {
    POPS, 
    INGREDIENT, 
    FROSTINGS
};


enum class GameState {
    LOST, 
    WON, 
    ONGOING
};


enum class MenuButtons {
    NOTHING, 
    PLAY, 
    BACK, 
    GAME_OVER, 
    GAME_ONGOING, 
    LEVEL1, 
    LEVEL2, 
    LEVEL3
};


#endif