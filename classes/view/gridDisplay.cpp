#include "gridDisplay.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                      Private Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


void GridDisplay::resetGrid() {
    for (int i = 0; i < ROWS; ++i) {
        visualComponents.push_back({});
        for (int j = 0; j < COLS; ++j) visualComponents[i].push_back({});
    }
}


/*-------------------------------------------------------------------------------------------*
 *                                      Animation                                           *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Pops the queue to get the next set of animations 
 *
 */
void GridDisplay::nextAnimation() {
    switch (animationQueue.nextAnimation()) {
        case AnimationType::Pop:
            performPop();
            break;
        case AnimationType::DropLeft:
            performDrop(Beneath::LEFT);
            break;
        case AnimationType::DropDown:
            performDrop(Beneath::CENTER);
            break;
        case AnimationType::DropRight:
            performDrop(Beneath::RIGHT);
            break;
        case AnimationType::Fill:
            performFill();
            break;
        case AnimationType::Swap:
            performSwap();
            break;
    }
}


/**
 * @brief Displays the fill animation
 *
 */
void GridDisplay::performFill() {
    std::vector<CoordComponent> toFill = animationQueue.nextFill();
    for (auto &cc : toFill) {
        Point coord = cc.first;
        ComponentType type = cc.second;

        visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, type);
        visualComponents[coord.y][coord.x]->fillAnimate();
    }
}


/**
 * @brief Displays the drop animation
 * 
 * @param direction
 * 
 */
void GridDisplay::performDrop(Beneath direction) {
    Point delta[] = {{-1, 1}, {0, 1}, {1, 1}};
    std::vector<Point> toDrop = animationQueue.nextDrop();
    for (auto &p : toDrop) {
        if (!visualComponents[p.y][p.x]) return;
        Point dest = p + delta[static_cast<int>(direction)];
        visualComponents[p.y][p.x]->moveAnimate(calculateCenter(dest));
        visualComponents[dest.y][dest.x] = visualComponents[p.y][p.x]; 
        visualComponents[p.y][p.x] = nullptr;
    } 

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
std::shared_ptr<ComponentDisplay> GridDisplay::factoryMethod(int row, int col, const ComponentType &component) const {
    std::shared_ptr<ComponentDisplay> ret;
    Point center = calculateCenter({col, row});
    switch (component.type) {
        case Component::CANDY:
            ret = std::make_shared<CandyDisplay>(center, component.colour);
            break;
        case Component::STRIPED_BOMB_H:
            ret = std::make_shared<StripedDisplay>(center, component.colour, Direction::HORIZONTAL);
            break;
        case Component::STRIPED_BOMB_V:
            ret = std::make_shared<StripedDisplay>(center, component.colour, Direction::VERTICAL);
            break;
        case Component::WRAPPED_BOMB:
            ret = std::make_shared<WrappedDisplay>(center, component.colour);
            break;
        case Component::WALL:
            ret = std::make_shared<WallDisplay>(center);
            break;
        case Component::FROSTING1:
            ret = std::make_shared<FrostingDisplay>(center, 1);
            break;
        case Component::FROSTING2:
            ret = std::make_shared<FrostingDisplay>(center, 2);
            break;
        case Component::SPECIAL_BOMB:
            ret = std::make_shared<SpecialDisplay>(center);
            break;
        case Component::CHERRY:
            ret = std::make_shared<CherryDisplay>(center);
            break;
        case Component::HAZELNUT:
            ret = std::make_shared<HazelnutDisplay>(center);
            break;
        default:
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

    resetGrid();

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
                && visualComponents[row][col]->animationType() == AnimPriority::CANT_IGNORE) isAnimation = true;
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
                && visualComponents[row][col]->animationType() == AnimPriority::CANT_IGNORE) isAnimation = true;
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
void GridDisplay::notifyInit(const Point &coord, const ComponentType &type) {
    visualComponents[coord.y][coord.x] = factoryMethod(coord.y, coord.x, type);
}


void GridDisplay::notifySwap(const Point &start, const Point &dest) {
    broadcast.clearHelpMessage();
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
    broadcast.setMessage(Constants::BAD_SWAP);
    animationQueue.enqueueSwap({c1, c2});
    animationQueue.enqueueSwap({c1, c2});
}


void GridDisplay::notifyNoSwaps() {
    broadcast.setMessage(Constants::SHUFFLING);
}


void GridDisplay::notifyGameState(GameState state) {
    switch (state) {
        case GameState::LOST:
            lost();
            break;
        case GameState::WON:
            won();
            break;
        default:
            break;
    }
}


void GridDisplay::notifyObjective(ObjectiveType objType, int obj) {
    broadcast.setObjective(objType, obj);
}

void GridDisplay::notifyObjective(ObjectiveType objType, int obj, Colour colour) {
    broadcast.setObjective(objType, obj, colour);
}

void GridDisplay::notifyReset() {
    animationQueue.clear();
    broadcast.clear();
}