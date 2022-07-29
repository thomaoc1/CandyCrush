#include "gridDisplay.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                      Private Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------*
 *                                      Animations                                           *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Pops the queue to get the next set of animations 
 *
 */
void GridDisplay::nextAnimation() {
    //package();
    switch (animationQueue.nextAnimation()) {
        case animations::Pop:
            performPop();
            break;
        case animations::DropLeft:
            performDrop(Constants::LEFT);
            break;
        case animations::DropDown:
            performDrop(Constants::CENTER);
            break;
        case animations::DropRight:
            performDrop(Constants::RIGHT);
            break;
        case animations::Fill:
            performFill();
            break;
        case animations::Swap:
            performSwap();
            break;
    }
    //package();
}


/**
 * @brief Displays the fill animation
 *
 */
void GridDisplay::performFill() {
    std::vector<CoordColour> toFill = animationQueue.nextFill();
    for (auto &cc : toFill) {
        Point coord = cc.first;
        visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, cc.second);
        visualComponents[coord.y][coord.x]->fillAnimate();
    }
    package();
}


/**
 * @brief Displays the drop animation
 * 
 * @param direction
 * 
 */
void GridDisplay::performDrop(int direction) {
    Point delta[] = {{-1, 1}, {0, 1}, {1, 1}};
    std::vector<Point> toDrop = animationQueue.nextDrop();
   
    for (auto &p : toDrop) {
        // Temporary
        if (!visualComponents[p.y][p.x]) return;
        Point dest = p + delta[direction];
        visualComponents[p.y][p.x]->moveAnimate(calculateCenter(dest));
        visualComponents[dest.y][dest.x] = visualComponents[p.y][p.x]; 
        visualComponents[p.y][p.x] = nullptr;
    } 
    package();
}


/**
 * @brief Displays the pop animation
 * 
 */
void GridDisplay::performPop() {
    std::vector<Point> toPop = animationQueue.nextPop();
    for (auto &p : toPop) {
        // Temporary check
        if (!visualComponents[p.y][p.x]) return;
        visualComponents[p.y][p.x]->popAnimate();
    }
    package();
}


/**
 * @brief Displays the swap animation
 * 
 * @param c1
 * @param c2
 * 
 */
void GridDisplay::performSwap() {
    CoordPair toSwap = animationQueue.nextSwap();

    Point c1 = toSwap.first, c2 = toSwap.second;
    std::swap(visualComponents[c2.y][c2.x], visualComponents[c1.y][c1.x]);
    visualComponents[c1.y][c1.x]->swapAnimate(visualComponents[c2.y][c2.x]);

    swapping = true;
    package();
}


/*-------------------------------------------------------------------------------------------*
 *                                       Utility                                             *
 *-------------------------------------------------------------------------------------------*/


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
        case Constants::RED_STRIPED_BOMB_V: 
        case Constants::BLUE_STRIPED_BOMB_V:
        case Constants::GREEN_STRIPED_BOMB_V:
        case Constants::YELLOW_STRIPED_BOMB_V:
        case Constants::PURPLE_STRIPED_BOMB_V:
        case Constants::ORANGE_STRIPED_BOMB_V:
            ret = std::make_shared<StripedDisplay>(center, Constants::associatedColour(component), Constants::VERTICAL);
            break;
        case Constants::RED_STRIPED_BOMB_H: 
        case Constants::BLUE_STRIPED_BOMB_H:
        case Constants::GREEN_STRIPED_BOMB_H:
        case Constants::YELLOW_STRIPED_BOMB_H:
        case Constants::PURPLE_STRIPED_BOMB_H:
        case Constants::ORANGE_STRIPED_BOMB_H:
            ret = std::make_shared<StripedDisplay>(center, Constants::associatedColour(component), Constants::HORIZONTAL);
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
        default:
            std::cout << component << ": uh oh" << std::endl;
            break;
     }
    return ret;
}


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


GridDisplay::GridDisplay() {
    for (int i = 0; i < 9; ++i) {
        visualComponents.push_back({});
        for (int j = 0; j < 9; ++j) visualComponents[i].push_back(nullptr);
    }
    for (int row = 0; row < 9; ++row) {
        std::vector<CellDisplay> tmp;
        for (int col = 0; col < 9; ++col) {
            tmp.emplace_back(Point{static_cast<int>(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2),
                                static_cast<int>(Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2)});
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
    if (!isAnimation && animationQueue.size() > 0){
        nextAnimation();
    }   
    else swapping = false;
}


/**
 * @brief Returns true if any components are being animated
 * 
 * @return bool
 * 
 */
bool GridDisplay::inAnimation() const {
    // std::cout << "inAnimation call" << std::endl;
    bool isAnimation = false;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!visualComponents[row][col]) continue; 
            if (visualComponents[row][col]->inAnimation()) isAnimation = true;
        }
    }
    // std::cout << "In animation: " << isAnimation << std::endl;
    return isAnimation;
}


/*-------------------------------------------------------------------------------------------*
 *                                   Observer Methods                                        *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Notify an initialisation insert 
 * 
 * @param coord
 * @param type
 *
 */
void GridDisplay::notifyInit(const Point &coord, int type) {
    visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, type);
    if (coord.x == 8 && coord.y == 8) package();
}


/**
 * @brief Notify a normal insert (fill)
 *
 * @param coord
 * @param type
 * 
 */
void GridDisplay::notifyInsert(const Point &coord, int type) {
    animationQueue.enqueueFill({{coord, type}});
}


/**
 * @brief Notify a fill 
 * 
 * @param toFill
 *
 */
void GridDisplay::notifyFill(const std::vector<CoordColour> &toFill) {
    animationQueue.enqueueFill(toFill);
}


/**
 * @brief Notify a pop / suppression
 * 
 * @param toPop
 *
 */
void GridDisplay::notifyPop(const std::vector<Point> &toPop) {
    animationQueue.enqueuePop(toPop);
}


/**
 * @brief Notify a drop
 * 
 * @param toDrop 
 * @param direction
 *
 */
void GridDisplay::notifyDrop(const std::vector<Point> &toDrop, int direction) {
    animationQueue.enqueueDrop(toDrop, direction);
}


/**
 * @brief Notify a swap
 * 
 * @param c1
 * @param c2
 *
 */
void GridDisplay::notifySwap(const Point &c1, const Point &c2) {
    if (!swapping && animationQueue.size() == 0) animationQueue.enqueueSwap({c1, c2});
}


void GridDisplay::notifyFailedSwap(const Point &, const Point &) {
    std::cout << "View Swap failed" << std::endl;
}


// TEMP
void GridDisplay::package() const {
    std::cout << "Packaging" << std::endl;
    std::string temp;

    for (int i = 0; i < 9; ++i) {
        if (i == 0) temp += "   " + std::to_string(i)+ "    ";
        else temp += std::to_string(i) + "    ";
    }
    temp += "\n============================================\n";

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j == 0) temp += std::to_string(i) + "| ";
            std::string component = " ";
            if (visualComponents[i][j]) component = visualComponents[i][j]->type();
            if (component.length() == 1) temp += component + "    ";
            else if (component.length() == 2) temp += component + "   ";
            else if (component.length() == 3) temp += component + "  ";
            else temp += component + " ";
        }
        temp += "\n";
    }
    
    // std::cout << temp << std::endl;

    Log::get().addViewMessage(temp);

    //auto &log = Log::get();
    //log.addViewMessage(temp);
}