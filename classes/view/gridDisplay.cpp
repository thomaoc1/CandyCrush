#include "gridDisplay.hpp"


void GridDisplay::reconstructGrid() {
    visualGrid.clear();
    for (int row = 0; row < Grid::ROWS; ++row) {
        std::vector<CellDisplay> tmp = {};
        for (int col = 0; col < Grid::COLS; ++col) {
            int component = grid->getCell(row, col);
            switch (component) {
                case Constants::RED:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;        
                case Constants::BLUE:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;
                case Constants::GREEN:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;
                case Constants::PURPLE:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;
                case Constants::YELLOW:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;
                case Constants::ORANGE:
                    tmp.push_back(CellDisplay{std::make_shared<CandyDisplay>(component), row, col});
                    break;
                case Constants::RED_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::RED), row, col});
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::BLUE), row, col});
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::GREEN), row, col});
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::YELLOW), row, col});
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::PURPLE), row, col});
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<StripedDisplay>(Constants::ORANGE), row, col});
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::RED), row, col});
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::BLUE), row, col});
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::GREEN), row, col});
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::YELLOW), row, col});
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::PURPLE), row, col});
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    tmp.push_back(CellDisplay{std::make_shared<WrappedDisplay>(Constants::ORANGE), row, col});
                    break;
                case Constants::WALL:
                    tmp.push_back(CellDisplay{std::make_shared<WallDisplay>(), row, col});
                    break;
            }
        }
        visualGrid.push_back(tmp);
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
            visualGrid[row][col].draw();
        }
    }
}