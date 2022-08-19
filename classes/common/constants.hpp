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
    static const std::string BAD_SWAP;
    static const std::string GAME_WON;
    static const std::string GAME_LOST;
    static const std::string SHUFFLING;
    
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
    static const double CANDY_RADIUS;

    static const int COLS;
    static const int ROWS;

    static Component directionToSt(Direction direction);
};



#endif