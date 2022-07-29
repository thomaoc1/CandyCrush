#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>


class Constants {
    const static std::array< int, 6 > candies;
public:

    /* Model Constants */
    enum directions{VERTICAL, HORIZONTAL, NO_DIRECTION} directions;
    static enum {LEFT, CENTER, RIGHT} below;
    static enum actions{DISPLACEMENT, SWAP, SUPPRESSION} actions;

    /* View Constants */
    static const double FPS;
    static const double WINDOW_HEIGHT;
    static const double WINDOW_WIDTH;
    static const double GAME_WINDOW_Yi;
    static const double GAME_WINDOW_Xi;
    static const double GAME_WINDOW_Yf;
    static const double GAME_WINDOW_Xf;
    static const double INTER_CELL;
    static const double CANDY_RADIUS;

    static enum animations{NO_ANIMATION, MOVE_ANIMATION, SUPPRESION_ANIMATION} animations;


    static enum components{RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, BLACK, NONE, ALL, EMPTY, IMMOBILE, 

                            RED_STRIPED_BOMB_V, BLUE_STRIPED_BOMB_V, GREEN_STRIPED_BOMB_V, YELLOW_STRIPED_BOMB_V,
                            PURPLE_STRIPED_BOMB_V, ORANGE_STRIPED_BOMB_V,
                            RED_STRIPED_BOMB_H, BLUE_STRIPED_BOMB_H, GREEN_STRIPED_BOMB_H, YELLOW_STRIPED_BOMB_H,
                            PURPLE_STRIPED_BOMB_H, ORANGE_STRIPED_BOMB_H,

                            RED_WRAPPED_BOMB, BLUE_WRAPPED_BOMB, GREEN_WRAPPED_BOMB, YELLOW_WRAPPED_BOMB,
                            PURPLE_WRAPPED_BOMB, ORANGE_WRAPPED_BOMB,

                            SPECIAL_BOMB} components;

    
    static int randomCandy() {return candies[rand() % 6];}
    static int randomDirection() {return rand() % 2;}
    
    static int associatedColour(int component);
    static Fl_Color associatedFLColour(int colour);
    static int associatedStripedBomb(int colour, int direction);
    static int associatedWrappedBomb(int colour);
    
};



#endif