#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <string>
#include <array>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "enumerations.hpp"
#include "componentType.hpp"

class Constants {
public:

    /* Model Constants */
    static enum directions{VERTICAL, HORIZONTAL, NO_DIRECTION} directions;
    static enum {LEFT, CENTER, RIGHT} below;

    static const std::string badSwap;
    static const std::string gameWon;
    static const std::string gameLost;
    static const std::string shuffling;
    
    static const double FPS;
    static const double WINDOW_HEIGHT;
    static const double WINDOW_WIDTH;
    static const double GAME_WINDOW_Yi;
    static const double GAME_WINDOW_Xi;
    static const double GAME_WINDOW_Yf;
    static const double GAME_WINDOW_Xf;
    
    static const double CELL_SIZE;
    static const double HALVE_CELL_SIZE;
    static const double STEP_SIZE;
    static const double GAP_SIZE;
    static const double GRIDSIZE;
    static const double HALVE_GRIDSIZE;
    static const int COLS;
    static const int ROWS;

    static const double CANDY_RADIUS;

    static enum gameState{LOST, WON, ONGOING} gamestate;

    static enum animTypes{IGNORE, CANT_IGNORE} animTypes;

    static enum blastTypes{NO_BLAST, SIMPLE, STRIPED, WRAPPED, SPECIAL} blastTypes;

    static enum objectiveTypes{POPS, INGREDIENT, FROSTINGS} objectives;

    /** @brief Returns a random candy */
    static Colour randomColour() {return static_cast<Colour>(static_cast<Colour>(rand() % 6));}

    /** @brief Returns a random direction (horizontal / verical) */
    static Direction randomDirection() {return static_cast<Direction>(rand() % 2);}
    static Direction perpendicular(Direction dir);

    static int associatedColour(int component);
    static Fl_Color associatedFLColour(Colour colour);
    static int associatedBlast(int component);
    static Component directionToSt(Direction direction);
    static int colourToWr(int colour);
    
};



#endif