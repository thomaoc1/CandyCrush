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
    // fl_color(FL_BLACK);
    fl_draw_box(FL_FLAT_BOX, Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, FL_BLACK);
}


void GridDisplay::reconstructGrid() {
    for (int row = 0; row < Grid::ROWS; ++row) {
        visualGrid.emplace_back(std::vector<CellDisplay>(Grid::COLS));
        for (int col = 0; col < Grid::COLS; ++col) {
            int component = grid->getCell(row, col);
            switch (component) {
                case Constants::RED:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;        
                case Constants::BLUE:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;
                case Constants::GREEN:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;
                case Constants::PURPLE:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;
                case Constants::YELLOW:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;
                case Constants::ORANGE:
                    visualGrid[row][col].setOccupied(std::make_shared<CandyDisplay>(component));
                    break;
                case Constants::RED_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(FL_RED));
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(FL_BLUE));
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(FL_GREEN));
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(FL_YELLOW));
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(FL_MAGENTA));
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(fl_rgb_color(255,165,0)));
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(FL_RED));
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(FL_BLUE));
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(FL_GREEN));
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(FL_YELLOW));
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(FL_MAGENTA));
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(fl_rgb_color(255,165,0)));
                    break;
                case Constants::WALL:
                    visualGrid[row][col].setOccupied(std::make_shared<WallDisplay>());
                    break;
            }
        }
    }
}


// public


GridDisplay::GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {
    reconstructGrid();
}


void GridDisplay::draw()  {

    /* In the case that something has happened that hasn't already happened */
    if (events != grid->getEvents() && grid->occurence()) { 
        events = grid->getEvents();
        for (int i = 0; i < events.eventLength(); ++i) {
            switch(events.getAction(i)->type()) {
                case Constants::DROP:
                    std::cout << "Dropped" << std::endl;
                    break;
                case Constants::SWAP:
                    std::cout << "Swapped" << std::endl;
                    break;
                case Constants::POP:
                    std::cout << "Popped" << std::endl;
                    break;
            }
        }
    }

    // TODO: 1. Reconstruction of visual grid
    // TODO: 2. Displaying grid
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