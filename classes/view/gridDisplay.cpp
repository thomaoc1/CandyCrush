#include "gridDisplay.hpp"


void GridDisplay::drawCell(int x, int y) const {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, FL_BLACK);
}


void GridDisplay::drawCandy(int colour, int x, int y) const {
    fl_color(colour);
    fl_begin_polygon();
    fl_circle(Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi, 
                Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}


void GridDisplay::draw() const {
    for (int i = 0; i < Grid::ROWS; ++i) {
        for (int j = 0; j < Grid::COLS; ++j) {
            drawCell(i, j);
            switch (grid->getCell(i, j)) {
                case Constants::RED:
                    fl_color(FL_DARK_RED);
                    break;        
                case Constants::BLUE:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN:
                    fl_color(FL_GREEN);
                    break;
                case Constants::PURPLE:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::YELLOW:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::ORANGE:
                    fl_color(FL_RED);
                    break;
                case Constants::RED_STRIPED_BOMB:
                    fl_color(FL_DARK_RED);
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    fl_color(FL_GREEN);
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    fl_color(FL_RED);
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    fl_color(FL_DARK_RED);
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    fl_color(FL_GREEN);
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    fl_color(FL_RED);
                    break;
                case Constants::WALL:
                    fl_color(FL_BLACK);
                    break;
            }
            fl_begin_polygon();
            fl_circle(Constants::INTER_CELL * j + Constants::GAME_WINDOW_Xi + Constants::CANDY_RADIUS + 3 /*TODO*/, 
                        Constants::INTER_CELL * i + Constants::GAME_WINDOW_Yi + Constants::CANDY_RADIUS + 3 /*TODO*/, 
                        Constants::CANDY_RADIUS);
            fl_end_polygon();
        }
    }
}