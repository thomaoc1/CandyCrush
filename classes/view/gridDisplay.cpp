#include "gridDisplay.hpp"


void GridDisplay::drawWall(int x, int y) const {
    // fl_color(FL_BLACK);
    fl_draw_box(FL_FLAT_BOX, Constants::INTER_CELL * x + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * y + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, FL_BLACK);
}


void GridDisplay::reconstructGrid() {
    for (int row = 0; row < Grid::ROWS; ++row) {
        visualGrid.push_back(std::vector<CellDisplay>(Grid::COLS));
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
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::RED));
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::BLUE));
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::GREEN));
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::YELLOW));
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::PURPLE));
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<StripedDisplay>(Constants::ORANGE));
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::RED));
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::BLUE));
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::GREEN));
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::YELLOW));
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::PURPLE));
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    visualGrid[row][col].setOccupied(std::make_shared<WrappedDisplay>(Constants::ORANGE));
                    break;
                case Constants::WALL:
                    visualGrid[row][col].setOccupied(std::make_shared<WallDisplay>());
                    break;
            }
        }
    }
}


// public


GridDisplay::GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {reconstructGrid();}


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
        reconstructGrid();
    }

    // TODO: 1. Reconstruction of visual grid
    // TODO: 2. Displaying grid
    for (int row = 0; row < Grid::ROWS; ++row) {
        for (int col = 0; col < Grid::COLS; ++col) {
            visualGrid[row][col].draw(row, col);
        }
    }
}