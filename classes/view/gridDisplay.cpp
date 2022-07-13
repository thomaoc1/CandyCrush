#include "gridDisplay.hpp"


void GridDisplay::componentMove(std::shared_ptr<Action> move) {
    // Starting indices in the visualComponents matrix
    Point start = move->getStart();
    Point dest = move->getDest();
    std::cout << start.y << " " << start.x << std::endl;
    std::cout << dest.y << " " << dest.x << std::endl;
    
    visualComponents[start.y][start.x]->moveAnimate(calculateCenter(dest.y, dest.x));
    visualComponents[dest.y][dest.x] = visualComponents[start.y][start.x];
    //visualComponents[start.y][start.x] = std::shared_ptr<ComponentDisplay>{nullptr};
}


void GridDisplay::componentRemove(std::shared_ptr<Action> remove) {
    Point coord = remove->getStart();
    visualComponents[coord.x][coord.y] = nullptr;
}

/*
void GridDisplay::componentSwap(std::shared_ptr<Action> swap) {
    Point coord1 = swap->getStart();
    Point coord2 = swap->getDest();
    std::shared_ptr<ColouredComponent> component1 = std::dynamic_pointer_cast<ColouredComponent>(visualComponents[coord1.y][coord1.x]);
    std::shared_ptr<ColouredComponent> component2 = std::dynamic_pointer_cast<ColouredComponent>(visualComponents[coord2.y][coord2.x]);
    component1->moveAnimate(calculateCenter(coord2.y, coord2.x));
    component2->moveAnimate(calculateCenter(coord1.y, coord1.x));
*/
/**
 * @brief Calculates the center of the shape based on its location in the reconstructed
 *  matrix
 * 
 * @param row 
 * @param col 
 * @return Point 
 */
Point GridDisplay::calculateCenter(int row, int col) const {
    return {static_cast<int>(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2),
            static_cast<int>(Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2)};
}


/**
 * @brief Returns associated colour for every component (namely bombs/specials)
 * 
 * @param component 
 * @return int 
 */
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


/**
 * @brief Factory method design pattern used to construct the correct object given its enum
 * 
 * @param row 
 * @param col 
 * @param component 
 * @return std::shared_ptr<ComponentDisplay> 
 */
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


/**
 * @brief Reconstructs the grid with visual representations
 * 
 */
void GridDisplay::reconstructGrid() {
    visualComponents.clear();
    for (int row = 0; row < Grid::ROWS; ++row) {
        std::vector< std::shared_ptr<ComponentDisplay> > tmp;
        for (int col = 0; col < Grid::COLS; ++col) tmp.push_back(factoryMethod(row, col, grid->getCell(row, col)));
        visualComponents.push_back(tmp);
    }
}

/**
 * @brief Construct a new GridDisplay object
 * 
 * @param grid 
 */
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


/**
 * @brief Displays the reconstructed grid and animations
 * 
 */
void GridDisplay::draw()  {

    /* In the case that something has happened that hasn't already happened */
    if (events != grid->getEvents() && grid->occurence()) { 
        events = grid->getEvents();
        for (int i = 0; i < events.eventLength(); ++i) {
            switch(events.getAction(i)->type()) {
                case Constants::DISPLACEMENT:
                    std::cout << "Dropped" << std::endl;
                    componentMove(events.getAction(i));
                    break;
                case Constants::SWAP:
                    std::cout << "Swapped" << std::endl;
                    break;
                case Constants::SUPPRESSION:
                    std::cout << "Popped" << std::endl;
                    break;
            }
        }
    } 


    bool animations = false; 
    for (auto &row : visualComponents) {
        for (auto &c : row) {
            if (c && c->inAnimation()) {
                animations = true;
                break;
            }
        }
    }
    if (!animations) reconstructGrid();
        

    // TODO: 2. Displaying grid
    for (int row = 0; row < Grid::ROWS; ++row) {
        for (int col = 0; col < Grid::COLS; ++col) {
            visualGrid[row][col].draw();
            if (visualComponents[row][col]) visualComponents[row][col]->draw();
        }
    }
}