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
}


/**
 * @brief Displays the fill animation
 *
 */
void GridDisplay::performFill() {
    std::vector<CoordColour> toFill = animationQueue.nextFill();
    for (auto &cc : toFill) {
        Point coord = cc.first;
        int type = cc.second;

        visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, type);
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
        if (!visualComponents[p.y][p.x]) continue;
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

    // swapping = true;
    package();
}


void GridDisplay::performSuggestion() {
    visualComponents[suggestion.first.y][suggestion.first.x]->suggAnimate();
    visualComponents[suggestion.second.y][suggestion.second.x]->suggAnimate();
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
    return {static_cast<int>( Constants::HALVE_CELL_SIZE * (coord.x + 1) + coord.x * Constants::STEP_SIZE + Constants::WINDOW_WIDTH/2 - Constants::HALVE_GRIDSIZE ),
            static_cast<int>(Constants::HALVE_CELL_SIZE * (coord.y + 1) + coord.y * Constants::STEP_SIZE + ((Constants::WINDOW_HEIGHT*3)/5) - Constants::HALVE_GRIDSIZE)};
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
        case Constants::FROSTING1:
            ret = std::make_shared<FrostingDisplay>(center, 1);
            break;
        case Constants::FROSTING2:
            ret = std::make_shared<FrostingDisplay>(center, 2);
            break;
        case Constants::SPECIAL_BOMB:
            ret = std::make_shared<SpecialDisplay>(center);
            break;
        case Constants::CHERRY:
            ret = std::make_shared<CherryDisplay>(center);
            break;
        case Constants::HAZELNUT:
            ret = std::make_shared<HazelnutDisplay>(center);
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
    for (int i = 0; i < ROWS; ++i) {
        visualComponents.push_back({});
        for (int j = 0; j < COLS; ++j) visualComponents[i].push_back({});
    }
    for (int row = 0; row < ROWS; ++row) {
        std::vector<CellDisplay> tmp;
        for (int col = 0; col < COLS; ++col) {
            tmp.emplace_back(CellDisplay{Point{static_cast<int>( Constants::HALVE_CELL_SIZE * (col + 1) + col * Constants::STEP_SIZE + Constants::WINDOW_WIDTH/2 - Constants::HALVE_GRIDSIZE ),
                                static_cast<int>( Constants::HALVE_CELL_SIZE * (row + 1) + row * Constants::STEP_SIZE + ((Constants::WINDOW_HEIGHT*3)/5) - Constants::HALVE_GRIDSIZE) }});
        }
        visualGrid.push_back(std::move(tmp));
    }
}


/**
 * @brief Displays the reconstructed grid and animations
 * 
 */
void GridDisplay::draw()  {
    broadcast.draw();
    
    if (time == suggestionTime)  {
        performSuggestion();
        time = 0;
    }
    bool isAnimation = false;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            visualGrid[row][col].draw();
            if (!visualComponents[row][col]) continue; 
            if (visualComponents[row][col]->inAnimation() 
                && visualComponents[row][col]->animationType() == Constants::CANT_IGNORE) isAnimation = true;
            visualComponents[row][col]->draw();
        }
    }
    if (!isAnimation && animationQueue.size() > 0) {
        nextAnimation();
        time = 0;
    }
    if (!isAnimation) ++time;
}


/**
 * @brief Returns true if any components are being animated
 * 
 * @return bool
 * 
 */
bool GridDisplay::inAnimation() const {
    bool isAnimation = false;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (!visualComponents[row][col]) continue; 
            if (visualComponents[row][col]->inAnimation() 
                && visualComponents[row][col]->animationType() == Constants::CANT_IGNORE) isAnimation = true;
        }
    }
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
}


void GridDisplay::notifySwap(const Point &start, const Point &dest) {
    broadcast.clear();
    animationQueue.enqueueSwap({start, dest});
}


/**
 * @brief Performs a double swap animation
 * 
 * @param c1 
 * @param c2 
 * 
 */
void GridDisplay::notifyFailedSwap(const Point &c1, const Point &c2) {
    broadcast.setMessage("Can't swap those, try again.");
    animationQueue.enqueueSwap({c1, c2});
    animationQueue.enqueueSwap({c1, c2});
}


void GridDisplay::notifyNoSwaps() {
    broadcast.setMessage("There were possible swaps, shuffling.");
}


// TEMP
void GridDisplay::package() const {
    std::string temp;

    for (int i = 0; i < COLS; ++i) {
        if (i == 0) temp += "   " + std::to_string(i)+ "    ";
        else temp += std::to_string(i) + "    ";
    }
    temp += "\n============================================\n";

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
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

    Log::get().addViewMessage(temp);
}