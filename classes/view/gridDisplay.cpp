#include "gridDisplay.hpp"


void GridDisplay::drawCell(int x, int y) const {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, FL_BLACK);
}


void GridDisplay::drawCandy(int colour, int x, int y) const {
    fl_color(colour);
    fl_begin_polygon();
    fl_circle(Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2, 
                Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}


void GridDisplay::drawWrappedBomb(int /* colour */, int /* x */, int /* y */) const {

}


void GridDisplay::drawStripedBomb(int /* colour */, int /* x */, int /* y */) const {

}


void GridDisplay::drawWall(int x, int y) const {
    fl_color(FL_BLACK);
    fl_draw_box(FL_FLAT_BOX, Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, FL_BLACK);
}


void GridDisplay::draw() const {
    for (int i = 0; i < Grid::ROWS; ++i) {
        for (int j = 0; j < Grid::COLS; ++j) {
            drawCell(i, j);
            switch (grid->getCell(i, j)) {
                case Constants::RED:
                    drawCandy(FL_RED,j, i);
                    break;        
                case Constants::BLUE:
                    drawCandy(FL_BLUE,j, i);
                    break;
                case Constants::GREEN:
                    drawCandy(FL_GREEN,j, i);
                    break;
                case Constants::PURPLE:
                    drawCandy(FL_MAGENTA,j, i);
                    break;
                case Constants::YELLOW:
                    drawCandy(FL_YELLOW,j, i);
                    break;
                case Constants::ORANGE:
                    drawCandy(fl_rgb_color(255,165,0) ,j, i);
                    break;
                case Constants::RED_STRIPED_BOMB:
                    drawCandy(FL_RED,j, i);
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    drawCandy(FL_BLUE,j, i);
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    drawCandy(FL_GREEN,j, i);
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    drawCandy(FL_YELLOW, j, i);
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    drawCandy(FL_MAGENTA,j, i);
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    drawCandy(fl_rgb_color(255,165,0),j, i);
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    drawCandy(FL_RED,j, i);
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    drawCandy(FL_BLUE,j, i);
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    drawCandy(FL_GREEN,j, i);
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    drawCandy(FL_YELLOW, j, i);
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    drawCandy(FL_MAGENTA,j, i);
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    drawCandy(fl_rgb_color(255,165,0),j, i);
                    break;
                case Constants::WALL:
                    drawWall(j, i);
                    break;
            }
            
        }
    }
}