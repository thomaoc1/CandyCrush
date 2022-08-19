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


enum class AnimTypes {
    IGNORE, 
    CANT_IGNORE
};


enum class ObjectiveTypes {
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