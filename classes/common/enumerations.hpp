#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP


enum class Components {
    RED, 
    BLUE, 
    GREEN, 
    YELLOW, 
    PURPLE, 
    ORANGE,

    RED_STRIPED_BOMB_V, 
    BLUE_STRIPED_BOMB_V, 
    GREEN_STRIPED_BOMB_V, 
    YELLOW_STRIPED_BOMB_V,
    PURPLE_STRIPED_BOMB_V, 
    ORANGE_STRIPED_BOMB_V,

    RED_STRIPED_BOMB_H, 
    BLUE_STRIPED_BOMB_H, 
    GREEN_STRIPED_BOMB_H, 
    YELLOW_STRIPED_BOMB_H,
    PURPLE_STRIPED_BOMB_H, 
    ORANGE_STRIPED_BOMB_H, 

    RED_WRAPPED_BOMB, 
    BLUE_WRAPPED_BOMB, 
    GREEN_WRAPPED_BOMB, 
    YELLOW_WRAPPED_BOMB,
    PURPLE_WRAPPED_BOMB, 
    ORANGE_WRAPPED_BOMB,

    SPECIAL_BOMB,

    FROSTING1, 
    FROSTING2,
    CHERRY, 
    HAZELNUT,

    BLACK, 
    NONE, 
    ANY, 
    EMPTY, 
    WALL, 
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