#include "gridDisplay.hpp"


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
            ret = std::make_shared<StripedDisplay>(center, Constants::associatedColour(component));
            break;
        case Constants::RED_WRAPPED_BOMB: 
        case Constants::BLUE_WRAPPED_BOMB:
        case Constants::GREEN_WRAPPED_BOMB:
        case Constants::YELLOW_WRAPPED_BOMB:
        case Constants::PURPLE_WRAPPED_BOMB:
        case Constants::ORANGE_WRAPPED_BOMB:
            ret = std::make_shared<WrappedDisplay>(center, Constants::associatedColour(component));
            break;
        case Constants::WALL:
            ret = std::make_shared<WallDisplay>(center);
            break;
    }
    return ret;
}


GridDisplay::GridDisplay() {
    for (int i = 0; i < 9; ++i) visualComponents.push_back({});
    for (int row = 0; row < 9; ++row) {
        std::vector<CellDisplay> tmp;
        for (int col = 0; col < 9; ++col) {
            tmp.push_back(Point{static_cast<int>(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi),
                                static_cast<int>(Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi)});
        }
        visualGrid.push_back(std::move(tmp));
    }
}


/**
 * @brief Displays the reconstructed grid and animations
 * 
 */
void GridDisplay::draw()  {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            visualGrid[row][col].draw();
            if (visualComponents[row][col]) visualComponents[row][col]->draw();
        }
    }
}


void GridDisplay::notifyInsert(const Point &coord, int type) {
    visualComponents[coord.y].push_back(factoryMethod(coord.y, coord.x, type));
}


void GridDisplay::notifySwap(const Point &c1, const Point &c2) {
    std::cout << "Swap notified received !" << std::endl;
    visualComponents[c1.y][c1.x]->swapAnimate(visualComponents[c2.y][c2.x]);
}