#include "gridDisplay.hpp"


void GridDisplay::nextAnimation() {
    switch (animationQueue.front()) {
        case animations::Pop:
            performPop();
            break;
        case animations::DropLeft:
            performDrop(Constants::BELOW_LEFT);
            break;
        case animations::DropDown:
            performDrop(Constants::BELOW);
            break;
        case animations::DropRight:
            performDrop(Constants::BELOW_RIGHT);
            break;
        case animations::Fill:
            performFill();
            break;
    }
    animationQueue.pop();
}


void GridDisplay::performFill() {
    std::vector<CoordColour> toFill = fillQueue.front();
    fillQueue.pop();
    for (auto &cc : toFill) {
        Point coord = cc.first;
        visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, cc.second);
        visualComponents[coord.y][coord.x]->fillAnimate();
    }
}


void GridDisplay::performDrop(int direction) {
    Point delta[] = {{-1, 1}, {0, 1}, {1, 1}};
    std::vector<Point> toDrop = dropQueue.front();
    dropQueue.pop();
   
    for (auto &p : toDrop) {
        // Temporary
        if (!visualComponents[p.y][p.x]) return;
        
        Point dest = p + delta[direction];
        visualComponents[p.y][p.x]->moveAnimate(calculateCenter(dest));
        visualComponents[dest.y][dest.x] = visualComponents[p.y][p.x]; 
        visualComponents[p.y][p.x] = nullptr;
    } 
}


void GridDisplay::performPop() {
    std::vector<Point> toPop = popQueue.front();
    popQueue.pop();
    for (auto &p : toPop) {
        // Temporary check
        if (!visualComponents[p.y][p.x]) return;
        visualComponents[p.y][p.x]->popAnimate();
    }
}


void GridDisplay::performSwap(const Point &c1, const Point &c2) {
    std::swap(visualComponents[c2.y][c2.x], visualComponents[c1.y][c1.x]);
    visualComponents[c1.y][c1.x]->swapAnimate(visualComponents[c2.y][c2.x]);
    swapping = true;
}

/**
 * @brief Calculates the center of the shape based on its location in the reconstructed
 *  matrix
 * 
 * @param row 
 * @param col 
 * @return Point 
 */
Point GridDisplay::calculateCenter(const Point &coord) const {
    return {static_cast<int>(Constants::INTER_CELL * coord.x + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2),
            static_cast<int>(Constants::INTER_CELL * coord.y + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2)};
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
    Point center = calculateCenter({col, row});
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
    bool isAnimation = false;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            visualGrid[row][col].draw();
            if (!visualComponents[row][col]) continue; 
            if (visualComponents[row][col]->inAnimation()) isAnimation = true;
            visualComponents[row][col]->draw();
        }
    }
    if (!isAnimation && animationQueue.size() > 0) nextAnimation();
    else swapping = false;
}


void GridDisplay::notifyInit(const Point &coord, int type) {
    visualComponents[coord.y].push_back(factoryMethod(coord.y, coord.x, type));
}


void GridDisplay::notifyInsert(const Point &coord, int type) {
    animationQueue.push(animations::Fill);
    fillQueue.push({{coord, type}});
}


void GridDisplay::notifyFill(const std::vector<CoordColour> &toFill) {
    animationQueue.push(animations::Fill);
    fillQueue.push(toFill);
}


void GridDisplay::notifyPop(const std::vector<Point> &toPop) {
    animationQueue.push(animations::Pop);
    popQueue.push(toPop);
}


void GridDisplay::notifyDrop(const std::vector<Point> &toDrop, int direction) {
    switch (direction) {
        case Constants::BELOW:
            animationQueue.push(animations::DropDown);
            break;
        case Constants::BELOW_LEFT:
            animationQueue.push(animations::DropLeft);
            break;
        case Constants::BELOW_RIGHT:
            animationQueue.push(animations::DropRight);
            break;
    }
    dropQueue.push(toDrop);
}


void GridDisplay::notifySwap(const Point &c1, const Point &c2) {
    if (!swapping) performSwap(c1, c2);
}
