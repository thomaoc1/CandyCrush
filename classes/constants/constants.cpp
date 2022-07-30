#include "constants.hpp"

const double Constants::FPS = 60;
const double Constants::WINDOW_HEIGHT = 750;
const double Constants::WINDOW_WIDTH = 750;
const double Constants::GAME_WINDOW_Yi = ((Constants::WINDOW_HEIGHT *3 ) /5 ) - Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Xi = Constants::WINDOW_WIDTH /2 - Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Yf = ((Constants::WINDOW_HEIGHT *3 ) /5 ) + Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Xf = Constants::WINDOW_WIDTH /2 + Constants::HALVE_GRIDSIZE;
const double Constants::CELL_SIZE = 50;

const double Constants::HALVE_CELL_SIZE = 25;
const double Constants::GAP_SIZE = 4;
const double Constants::STEP_SIZE = ( Constants::HALVE_CELL_SIZE + Constants::GAP_SIZE );
const double Constants::HALVE_GRIDSIZE = 5 * Constants::HALVE_CELL_SIZE + 4 * Constants::STEP_SIZE;

const int Constants::COLS = 9;
const int Constants::ROWS = 9;




const double Constants::CANDY_RADIUS = Constants::HALVE_CELL_SIZE - 3;


const std::array< int, 6 > Constants::candies = {components::RED, components::BLUE, components::GREEN, 
                                                    components::YELLOW, components::PURPLE, components::ORANGE};


int Constants::associatedColour(int component) {
    int colour;
    switch (component) {
        case Constants::RED:
        case Constants::BLUE:
        case Constants::GREEN:
        case Constants::YELLOW:
        case Constants::PURPLE:
        case Constants::ORANGE:
            colour = component;
            break;
        case Constants::RED_STRIPED_BOMB_V:
        case Constants::RED_STRIPED_BOMB_H:
        case Constants::RED_WRAPPED_BOMB:
            colour = Constants::RED;
            break;
        case Constants::BLUE_STRIPED_BOMB_V:
        case Constants::BLUE_STRIPED_BOMB_H:
        case Constants::BLUE_WRAPPED_BOMB:
            colour = Constants::BLUE;
            break;
        case Constants::GREEN_STRIPED_BOMB_V:
        case Constants::GREEN_STRIPED_BOMB_H:
        case Constants::GREEN_WRAPPED_BOMB:
            colour = Constants::GREEN;
            break;
        case Constants::YELLOW_STRIPED_BOMB_V:
        case Constants::YELLOW_STRIPED_BOMB_H:
        case Constants::YELLOW_WRAPPED_BOMB:
            colour = Constants::YELLOW;
            break;
        case Constants::PURPLE_STRIPED_BOMB_V:
        case Constants::PURPLE_STRIPED_BOMB_H:
        case Constants::PURPLE_WRAPPED_BOMB:
            colour = Constants::PURPLE;
            break;
        case Constants::ORANGE_STRIPED_BOMB_V:
        case Constants::ORANGE_STRIPED_BOMB_H:
        case Constants::ORANGE_WRAPPED_BOMB:
            colour = Constants::ORANGE;
            break;
        case Constants::WALL:
            colour = Constants::BLACK;
            break;
        case Constants::FROSTING1:
        case Constants::FROSTING2:
            colour = Constants::BLUE;
            break;
    }
    return colour;
}


Fl_Color Constants::associatedFLColour(int colour) {
    Fl_Color fl_colour;
    
    if (colour != Constants::SPECIAL_BOMB) colour = associatedColour(colour);
    else return FL_DARK_RED;

    switch(colour) {
        case Constants::RED:
            fl_colour = FL_RED;
            break;        
        case Constants::BLUE:
            fl_colour = FL_BLUE;
            break;
        case Constants::GREEN:
            fl_colour = FL_GREEN;
            break;
        case Constants::PURPLE:
            fl_colour = FL_MAGENTA;
            break;
        case Constants::YELLOW:
            fl_colour = FL_YELLOW;
            break;
        case Constants::ORANGE:
            fl_colour = fl_rgb_color(255,165,0);
            break;
        case Constants::BLACK:
            fl_colour = FL_BLACK;
            break;
    }
    return fl_colour;
}


int Constants::associatedStripedBomb(int colour, int direction) {
    int type;
    if (direction == Constants::VERTICAL) {
        switch (colour) {
            case Constants::RED:
                type = Constants::RED_STRIPED_BOMB_V;
                break;
            case Constants::BLUE:
                type = Constants::BLUE_STRIPED_BOMB_V;
                break;
            case Constants::GREEN:
                type = Constants::GREEN_STRIPED_BOMB_V;
                break;
            case Constants::YELLOW:
                type = Constants::YELLOW_STRIPED_BOMB_V;
                break;
            case Constants::PURPLE:
                type = Constants::PURPLE_STRIPED_BOMB_V;
                break;
            case Constants::ORANGE:
                type = Constants::ORANGE_STRIPED_BOMB_V;
                break;
        }
    }
    else {
        switch (colour) {
            case Constants::RED:
                type = Constants::RED_STRIPED_BOMB_H;
                break;
            case Constants::BLUE:
                type = Constants::BLUE_STRIPED_BOMB_H;
                break;
            case Constants::GREEN:
                type = Constants::GREEN_STRIPED_BOMB_H;
                break;
            case Constants::YELLOW:
                type = Constants::YELLOW_STRIPED_BOMB_H;
                break;
            case Constants::PURPLE:
                type = Constants::PURPLE_STRIPED_BOMB_H;
                break;
            case Constants::ORANGE:
                type = Constants::ORANGE_STRIPED_BOMB_H;
                break;
        }
    }
    return type;
}


int Constants::associatedWrappedBomb(int colour) {
    int type;
    switch (colour) {
        case Constants::RED:
            type = Constants::RED_WRAPPED_BOMB;
            break;
        case Constants::BLUE:
            type = Constants::BLUE_WRAPPED_BOMB;
            break;
        case Constants::GREEN:
            type = Constants::GREEN_WRAPPED_BOMB;
            break;
        case Constants::YELLOW:
            type = Constants::YELLOW_WRAPPED_BOMB;
            break;
        case Constants::PURPLE:
            type = Constants::PURPLE_WRAPPED_BOMB;
            break;
        case Constants::ORANGE:
            type = Constants::ORANGE_WRAPPED_BOMB;
            break;
    }
    return type;
}