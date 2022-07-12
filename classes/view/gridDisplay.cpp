#include "gridDisplay.hpp"


Point GridDisplay::calculateCenter(int row, int col) const {
    return {static_cast<int>(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2),
            static_cast<int>(Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2)};
}


int GridDisplay::associatedColour(int component) const {
    int ret;
    switch (component) {
        case Constants::RED_STRIPED_BOMB:
        case Constants::RED_WRAPPED_BOMB:
            ret = Constants::RED;
            break;
        case Constants::BLUE_STRIPED_BOMB:
        case Constants::BLUE_WRAPPED_BOMB:
            ret = Constants::BLUE;
            break;
        case Constants::GREEN_STRIPED_BOMB:
        case Constants::GREEN_WRAPPED_BOMB:
            ret = Constants::GREEN;
            break;
        case Constants::YELLOW_STRIPED_BOMB:
        case Constants::YELLOW_WRAPPED_BOMB:
            ret = Constants::YELLOW;
            break;
        case Constants::PURPLE_STRIPED_BOMB:
        case Constants::PURPLE_WRAPPED_BOMB:
            ret = Constants::PURPLE;
            break;
        case Constants::ORANGE_STRIPED_BOMB:
        case Constants::ORANGE_WRAPPED_BOMB:
            ret = Constants::ORANGE;
            break;
        default:
            ret = Constants::NONE;
            break;
    }
    return ret;
}


std::shared_ptr<ComponentDisplay> GridDisplay::factoryMethod(int row, int col, int component) const {
    std::shared_ptr<ComponentDisplay> ret;
    Point center = calculateCenter(row, col);
    switch (component) {
        case Constants::RED: 
        case Constants::BLUE:
        case Constants::GREEN:
        case Constants::YELLOW:
        case Constants::PURPLE:
        case Constants::ORANGE:
            ret = std::make_shared<CandyDisplay>(center, component);
            break;
        case Constants::RED_STRIPED_BOMB: 
        case Constants::BLUE_STRIPED_BOMB:
        case Constants::GREEN_STRIPED_BOMB:
        case Constants::YELLOW_STRIPED_BOMB:
        case Constants::PURPLE_STRIPED_BOMB:
        case Constants::ORANGE_STRIPED_BOMB:
            ret = std::make_shared<StripedDisplay>(center, associatedColour(component));
            break;
        case Constants::RED_WRAPPED_BOMB: 
        case Constants::BLUE_WRAPPED_BOMB:
        case Constants::GREEN_WRAPPED_BOMB:
        case Constants::YELLOW_WRAPPED_BOMB:
        case Constants::PURPLE_WRAPPED_BOMB:
        case Constants::ORANGE_WRAPPED_BOMB:
            ret = std::make_shared<WrappedDisplay>(center, associatedColour(component));
            break;
        case Constants::WALL:
            ret = std::make_shared<WallDisplay>(center);
            break;
    }
    return ret;
}


void GridDisplay::reconstructGrid() {
    visualComponents.clear();
    for (int row = 0; row < Grid::ROWS; ++row) {
        std::vector< std::shared_ptr<ComponentDisplay> > tmp;
        for (int col = 0; col < Grid::COLS; ++col) tmp.push_back(factoryMethod(row, col, grid->getCell(row, col)));
        visualComponents.push_back(tmp);
    }
}


// public


GridDisplay::GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {
    for (int row = 0; row < Grid::ROWS; ++row) {
        std::vector<CellDisplay> tmp;
        for (int col = 0; col < Grid::COLS; ++col) {
            tmp.push_back(Point{static_cast<int>(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi),
                                static_cast<int>(Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi)});
        }
        visualGrid.push_back(std::move(tmp));
    }
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
        reconstructGrid();
    }
    
    // TODO: 1. Reconstruction of visual grid
    // TODO: 2. Displaying grid
    for (int row = 0; row < Grid::ROWS; ++row) {
        for (int col = 0; col < Grid::COLS; ++col) {
            visualGrid[row][col].draw();
            visualComponents[row][col]->draw();
        }
    }
}