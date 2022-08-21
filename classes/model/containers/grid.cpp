#include "grid.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Private Methods                                     *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Initialises cells in grid
 * 
 */
void Grid::initialiseCells() {
    for (int row = 0; row < COLS; ++row) {
        std::vector<Cell> tmp = {};
        for (int col = 0; col < ROWS; ++col) tmp.emplace_back(Cell{row, col});
        grid.emplace_back(std::move(tmp));
    }
}


/**
 * @brief Fills in holes for after file insertions
 * 
 */
void Grid::completeGrid() {
    for (auto &row : grid) {
        for (auto &cell : row) {
            Point coord = cell.getLocation();
            cell.setNbs(getNbs(coord.y, coord.x));
            insertComponent(coord.y, coord.x);
            observer.notifyInit(coord, cell.component());
        } 
    }
}


/**
 * @brief Interprets files
 * 
 */
void Grid::fileInterpreter() {
    for (auto &ct : gd.components) {
        insertComponent(grid[ct.first.y][ct.first.x], ct.second);
        observer.notifyInit(ct.first, ct.second);
    }
}


/*-------------------------------------------------------------------------------------------*
 *                                        Grid Cleaning                                      *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Checks for Wrapped Bomb condition on a clear (L, X Shape clear with >=5 candies)
 * 
 * @param cColour
 * @param direction
 * 
 * @return bool
 * 
 */
void Grid::wrBombExtract(const std::vector< Cell * > &cColour, int index, Direction direction) {
    Direction perpendicular = (direction == Direction::HORIZONTAL ? Direction::VERTICAL : Direction::HORIZONTAL);
    std::vector< Cell * > cross = continuousColour(*cColour[index]).get(perpendicular);
    for (auto &cell : cross) willPop(*cell);
    bombs.push_back({cColour[index], ComponentType{cColour[index]->getColour(), Component::WRAPPED_BOMB}});
}


/**
 * @brief Checks for striped bomb condition (==4 candy clear)
 * 
 * @param cell
 * @param cColour
 * 
 * @return bool
 * 
 */
void Grid::stBombExtract(Cell &cell, Direction direction) {
    bombs.push_back({&cell, ComponentType{cell.getColour(), Constants::directionToSt(direction)}});
}


/**
 * @brief Extracts required bomb type from parameters given
 * 
 * @param cell 
 * @param cColour
 * @param b
 * 
 */
void Grid::bombExtract(Cell &cell, const std::vector< Cell * > &cColour, const BombInfo &bombData) {

    switch (bombData.type) {
            case CompType::Striped:
                stBombExtract(cell, bombData.direction);
                break;
            case CompType::Wrapped:
                wrBombExtract(cColour, bombData.index, bombData.direction);
                break;
            case CompType::Special:
                spBombExtract(cell);
                break;
            default:
                break;
        }
}


/**
 * @brief Checks a cell for every clear condition given a direction to check. Marks all cells
 *  which will be cleared with that cell.
 * 
 * @param cell
 * @param direciton
 * 
 */
void Grid::clearCheck(Cell &cell) {

    if (!isOccupied(cell) || cell.type() == Component::WALL 
                             || cell.type() == Component::CHERRY
                             || cell.type() == Component::HAZELNUT
                             || cell.getPop()) return;

    ColourNbs contColour = continuousColour(cell);
    if (!contColour.validity()) return;
        
    // Else at least 3 consecutives found 
    std::array<Direction, 2> directions = {Direction::VERTICAL, Direction::HORIZONTAL};
    BombInfo current;

    for (auto &dir : directions) {
        /* No combo condition*/
        if (contColour.size(dir) < 3) continue; 
        int index = wrSpawnCond(contColour.get(dir), dir);

        /* Special Bomb Condition */
        if (current.type < CompType::Special && spSpawnCond(contColour.get(dir))) 
            current = {CompType::Special, dir, -1};

        /* Wrapped Bomb Condition */
        else if (current.type < CompType::Wrapped && index >= 0) 
            current = {CompType::Wrapped, dir, index};

        /* Striped Bomb Condition */
        else if (current.type < CompType::Striped && stSpawnCond(contColour.get(dir))) 
            current = {CompType::Striped, dir, -1};
        
        for (auto &c : contColour.get(dir)) willPop(*c);
    }

    bombExtract(cell, contColour.get(current.direction), current);
}


/*-------------------------------------------------------------------------------------------*
 *                              Insertion / Suppression                                      *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Simulates wrapped candy explosion
 * 
 * @param target
 * 
 */
void Grid::wrappedBlast(Cell &target) {
    for (auto &c : target.getNbs()) 
        if (c) willPop(*c);
}


/**
 * @brief Simulates wrapped candy explosion
 * 
 * @param target
 * 
 */
void Grid::stripedBlast(Cell &target) {
    if (!isOccupied(target)) return;

    Point start = target.getLocation();
    std::vector<Cell *> tmp;

    if (target.type() == Component::STRIPED_BOMB_V) {
        for (int i = start.y + 1; i < ROWS; ++i) tmp.push_back(&grid[i][start.x]);
        for (int i = start.y - 1; i >= 0; --i) tmp.push_back(&grid[i][start.x]);
    }
    else {
        for (int i = start.x + 1; i < COLS; ++i) tmp.push_back(&grid[start.y][i]);
        for (int i = start.x - 1; i >= 0; --i) tmp.push_back(&grid[start.y][i]);
    }

    for (auto &c : tmp) willPop(*c);
}


/**
 * @brief Blast even when one of the elements in a swap is a Special Candy.
 * 
 * @param c1 
 * @param c2 
 */
void Grid::specialBlast(Cell &c1, Cell &c2) {

    if (c1.type() == Component::SPECIAL_BOMB && c2.type() == Component::SPECIAL_BOMB) {
        for (auto &row : grid) 
            for (auto &cell : row) willPop(cell);
    }

    else {
        Cell &target = c1.type() == Component::SPECIAL_BOMB ? c2 : c1;
        willPop(c1);
        willPop(c2);
        for (auto &row : grid) {
            for (auto &cell : row) {
                if (cell.getColour() != target.getColour()) continue;
                if (target.type() != Component::CANDY) insertComponent(cell, target.component());
                willPop(cell);
            }
        }
    }
}


/**
 * @brief Blast event when a Striped and Wrapped bomb are swapped.
 * 
 * @param c1 
 * @param c2 
 */
void Grid::wrStBlast(Cell &cell) {
    Point start = cell.getLocation();
    auto place = [&](Cell &c) -> void {
        c.setOccupied(std::make_shared<WrappedBomb>());
        willPop(c);
        wrappedBlast(c);
    };
    for (int i = start.y + 1; i < 9; i += 2) place(grid[i][start.x]); 
    for (int i = start.y - 1; i >= 0; i -= 2) place(grid[i][start.x]);
    for (int i = start.x + 1; i < 9; ++i) place(grid[start.y][i]);
    for (int i = start.x - 1; i >= 0; --i) place(grid[start.y][i]);
}


/**
 * @brief Treats a swap where both cells contains a bomb of any sort
 * 
 * @param c1
 * @param c2
 * 
 */
void Grid::bombSwap(Cell &c1, Cell &c2) {
    // Special && (anything)
    if (specialSwapCheck(c1, c2)) specialBlast(c1, c2);
    // (Striped && Striped) OR (Wrapped && Wrapped)
    else if (sameBomb(c1, c2)) {
        willPop(c1);
        willPop(c2);
    }
    // Striped && Wrapped
    else wrStBlast(c1);
}


/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 * 
 */
void Grid::unoccupy(Cell &target) {
    target.unOccupy();
    target.popped();
}


/**
 * @brief Clears frostings by treatint the associated vector
 * 
 */
void Grid::clearFrostings() {
    std::vector< Cell * > frostings;
    for (auto &cell : toPop) {
        if (cell->type() == Component::FROSTING1 || cell->type() == Component::FROSTING2) continue;
        for (auto &nb : cell->getCrossNbs()) {
            if (nb && !nb->getPop() 
                    && (nb->type() == Component::FROSTING2 || nb->type() == Component::FROSTING1)) {

                nb->willPop();
                toPop.push_back(nb);
                frostings.push_back(nb);
            }
        }
    }
    for (auto &cell : frostings) cell->popped();
}


/**
 * @brief Pops everything that needs to pop
 * 
 */
void Grid::popAll() {
    std::vector<Point> toObserver;
    std::vector< std::pair<Point, ComponentType> > filling;

    clearFrostings();

    for (auto &cell : toPop) {
        if (cell->compState() == ComponentState::POPPED) {
            if (cell->type() == Component::FROSTING2) gameObj.frostingPop();
            else gameObj.colourPop(cell->getColour());
            unoccupy(*cell);
        }
        else filling.push_back({cell->getLocation(), cell->component()});
        toObserver.push_back(cell->getLocation());
    }
    score.pop(static_cast<int>(toPop.size()));
    observer.notifyPop(toObserver);
    observer.notifyFill(filling);
    toPop.clear();
}


/**
 * @brief Marks a cell to be popped
 * 
 */
void Grid::willPop(Cell &target) {
    if (!isOccupied(target) || !canPop(target.type()) || target.getPop()) return;
    target.willPop();
    toPop.push_back(&target);
    if (wrBlastCond(target)) wrappedBlast(target);
    else if (stBlastCond(target)) stripedBlast(target);
}


/**
 * @brief Checks if Cherries or Hazels landed on the lowest row.
 * updates objectives and score. recalls
 * 
 */
void Grid::popIngredient() {
    for (auto &cell : grid[8]){
        if (cell.type() == Component::CHERRY || cell.type() == Component::HAZELNUT ) {
            gameObj.ingredientPop();
            cell.willPop();
            toPop.push_back(&cell);
        }
    }
}


/**
 * @brief Insert random game component at indices row, col into the Grid
 * 
 * @param row 
 * @param col 
 * 
 */
void Grid::insertComponent(int row, int col) {
    grid[row][col].setOccupied(std::make_shared<Candy>());
}


/**
 * @brief Insert specified component onto cell
 * 
 * @param cell
 * @param type
 * @param colour
 * 
 */
void Grid::insertComponent(Cell &cell, const ComponentType &component) {
    switch (component.type) {
        case Component::CANDY:
            cell.setOccupied(std::make_shared<Candy>(component.colour));
            break;
        case Component::STRIPED_BOMB_V:
            cell.setOccupied(std::make_shared<StripedBomb>(component.colour, Direction::VERTICAL));
            break;  
        case Component::STRIPED_BOMB_H:
            cell.setOccupied(std::make_shared<StripedBomb>(component.colour, Direction::HORIZONTAL));
            break;   
        case Component::WRAPPED_BOMB:
            cell.setOccupied(std::make_shared<WrappedBomb>(component.colour));
            break;
        case Component::SPECIAL_BOMB:
            cell.setOccupied(std::make_shared<SpecialBomb>());
            break;
        case Component::WALL:
            cell.setOccupied(std::make_shared<Wall>());
            break;
        case Component::CHERRY:
            cell.setOccupied(std::make_shared<Cherry>());
            break;
        case Component::HAZELNUT:
            cell.setOccupied(std::make_shared<Hazelnut>());
            break;
        case Component::FROSTING1:
            cell.setOccupied(std::make_shared<Frosting>(1));
            break;
        case Component::FROSTING2:
            cell.setOccupied(std::make_shared<Frosting>(2));
            break;
        default:
            break;
    }
}


/**
 * @brief Places all bombs
 * 
 */
void Grid::placeBombs() {
    int wrappedCount = 0;
    int stripedCount = 0;
    int specialCount = 0;

    for (auto &cc : bombs) {
        Cell &cell = *cc.first;
        ComponentType component = cc.second;
        insertComponent(cell, component);
        observer.notifyInsert(cell.getLocation(), cc.second);
        
        switch (component.type) {
            case Component::WRAPPED_BOMB:
                ++wrappedCount;
                break;
            case Component::STRIPED_BOMB_H:
            case Component::STRIPED_BOMB_V:
                ++specialCount;
                break;
            case Component::SPECIAL_BOMB:
                ++specialCount;
                break;
            default:
                break;
        }
    }
    score.bombSpawn(wrappedCount, Component::WRAPPED_BOMB);
    score.bombSpawn(stripedCount, Component::STRIPED_BOMB_V);
    score.bombSpawn(specialCount, Component::SPECIAL_BOMB);
    bombs.clear();
}


/**
 * @brief Swaps occupations of two cells
 * 
 * @param c1
 * @param c2
 * 
 */
void Grid::exchangeCells(Cell &c1, Cell &c2) {
    std::shared_ptr<GameComponent> tmp = std::move(c1.getOccupied());
    c1.setOccupied(std::move(c2.getOccupied()));
    c2.setOccupied(std::move(tmp));
}


/**
 * @brief Fills top row of grid
 * 
 */
bool Grid::fillTop() {
    using CoordComponent = std::pair< Point, ComponentType >;
    std::vector<CoordComponent> toFill;
    for (int i = 0; i < static_cast<int>(grid[0].size()); ++i) {
        if (isOccupied(grid[0][i])) continue;
        insertComponent(0, i);
        toFill.push_back(CoordComponent{{i, 0}, grid[0][i].component()});
    }

    if (toFill.size() > 0) 
        observer.notifyFill(toFill);
 
    return toFill.size() > 0;
}   


/**
 * @brief Refills entire grid with random candies
 * 
 */
void Grid::refillGrid() {
    for (auto &row : grid) {
        for (auto &cell : row) {
            insertComponent(cell.getLocation());
            observer.notifyInit(cell.getLocation(), cell.component());
        }
    }
}


/**
 * @brief Pops all continuous, same coloured Candies. Returns true if a pop has been performed and 
 *  false if not.
 * 
 * @return true 
 * @return false 
 */
bool Grid::clear() {
    bool clearGrid = true;
    
    // Going through every cell to find combo
    for (auto &row : grid) 
        for (auto &c : row) clearCheck(c);

    // Pops Cherries and hazels at the bottom
    popIngredient();
    
    if (toPop.size() > 0) {
        clearGrid = false;
        popAll();
        placeBombs();
    }

    
    return clearGrid;
}


/**
 * @brief Drop GameComponent in given direction if possible. If a candy has been dropped, returns true.
 * 
 * @param direction 
 * @return true 
 * @return false 
 */
bool Grid::directedDrop(Beneath direction) {
    std::vector<Point> toDrop;
    for (int i = ROWS - 1; i >= 0; --i) {
        for (int j = COLS - 1; j >= 0; --j) {

            Cell &cell = grid[i][j]; 

            if (!isOccupied(cell) || !isMobile(cell.type())) continue;   

            Cell * cellBeneath = cell.getBelow(direction);

            if (!cellBeneath || isOccupied(*cellBeneath)) continue;
            
            cellBeneath->setOccupied(cell.getOccupied());
            cell.unOccupy();
            toDrop.push_back(cell.getLocation());
            if (direction == Beneath::LEFT || direction == Beneath::RIGHT) break;   
        }
        if (toDrop.size() > 0 && (direction == Beneath::LEFT || direction == Beneath::RIGHT)) break;
    }
    if (toDrop.size() > 0) {
        observer.notifyDrop(toDrop, direction);
        fillTop();
    } 
    return toDrop.size() > 0;
}


/**
 * @brief Continously drops candies in correct order / direction
 * 
 */
void Grid::completeDrop() {
    bool dropComplete = false;
    while (!dropComplete)  {
        // Drop down until can't
        while(directedDrop(Beneath::CENTER));
        // DirectedDrop(Left) -> true : means at least one candy was dropped. !!! So restart DropDown 
        // DirectedDrop(Left) -> false : means no candy was dropped to the left, therefore start DropRight 
        if (!directedDrop(Beneath::LEFT)) {
            // DirectedDrop(Beneath) -> true : means at least candy was dropped. !!! So restart DropDown 
            // DirectedDrop(Right) -> false : means no candy was dropped to the Right, therefore Complete Drop 
            if (!directedDrop(Beneath::RIGHT)) dropComplete = true;
        }
    }
}


/**
 * @brief Combines all grid cleaning mechanics to clean up the grid
 * 
 */
void Grid::clean(Cell &c1, Cell &c2) {
    if (bombSwapCheck(c1, c2)) bombSwap(c1, c2);
    clean();
}


/**
 * @brief Combines all grid cleaning mechanics to clean up the grid.
 * 
 */
void Grid::clean() {
    while (!clear()) {
        completeFill();
        completeDrop();
        completeFill();
    } 
    if (!possibleMoves()) {
        observer.notifyNoSwaps();
        refillGrid();
        clean();
    }
    if (gameState() == GameState::WON) FileHandler().dumpScore(score.getScore());
}


/**
 * @brief  Verifies validity of a Candy swap. If valid, executes swap.
 * 
 * @param cell1 
 * @param cell2 
 * @return true 
 * @return false 
 */
bool Grid::checkSwap(const Point &cell1, const Point &cell2) {
    bool validity = false;
    Cell &c1 = grid[cell1.y][cell1.x];
    Cell &c2 = grid[cell2.y][cell2.x];
    if (!(isOccupied(c1) || isOccupied(c2)) 
            || !isMobile(c1.type())
            || !isMobile(c2.type())) return validity;

    exchangeCells(c1, c2);

    ColourNbs c1Nbs = continuousColour(c1);
    ColourNbs c2Nbs = continuousColour(c2);

    validity = c1Nbs.validity() || c2Nbs.validity();

    if (!validity) validity = bombSwapCheck(c1, c2);

    exchangeCells(c1, c2);

    return validity;
}


/*-------------------------------------------------------------------------------------------*
 *                             Sequential Colour Fetching                                    *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Returns continous Candy neighbours with identical colour as the source Candy on 
 *  the initial cell in the given orientation.
 * 
 * @param initial 
 * @param orientation
 * 
 * @return std::vector< Cell * > 
 * 
 */
std::vector< Cell * > Grid::colourDFS(Cell &initial, Direction orientation) const {
    const Colour colour = initial.getColour();
    std::vector< Cell * > continousColors = {&initial}; 
    
    // DFS
    std::vector< Cell * > stack = {&initial}; 
    Cell * current = &initial;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        std::vector< Cell * > nbs = orientation == Direction::VERTICAL ? current->getVertNbs() 
                                                                       : current->getHorizNbs();
        for (auto &nb : nbs) {
            if (std::find(continousColors.begin(), continousColors.end(), nb) != continousColors.end() 
                || nb->getColour() != colour) continue;
            
            // Elligible Candies
            stack.push_back(nb);
            continousColors.push_back(nb);
        }
    }
    return continousColors;
}


/**
 * @brief Returns vertical and horizontal sequential neighbours which have the same 
 *  colour as the GameComponent on the initial Cell.
 * 
 * @param initial
 * @return std::vector< std::vector< Cell * > >
 * 
 */
Grid::ColourNbs Grid::continuousColour(Cell &initial) const {
    ColourNbs ret;
    if (canPop(initial.type())) {
        std::vector< Cell * > v_cont = colourDFS(initial, Direction::VERTICAL);
        std::vector< Cell * > h_cont = colourDFS(initial, Direction::HORIZONTAL);
        ret.set(std::move(v_cont), std::move(h_cont));
    }
    return ret;
}


/*-------------------------------------------------------------------------------------------*
 *                                   Neighbour Fetching                                      *
 *-------------------------------------------------------------------------------------------*/


std::vector< Cell * > Grid::getNbs(int row, int col) {
    std::vector< Cell * > nbs(8, nullptr); 
    const std::vector<Point> DELTA = {{-1, -1}, {-1, 0}, {-1, 1},
                                      {0, -1}, {0, 1},
                                      {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < static_cast<int>(DELTA.size()); ++i) {
        int row_d = row + DELTA[i].x;
        int col_d = col + DELTA[i].y;

        if (inGrid({col_d, row_d})) continue;

        nbs[i] = &grid[row_d][col_d];
    }    
    return nbs; 
}


/*-------------------------------------------------------------------------------------------*
 *                                        Conditions                                         *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Checks if no swaps are possible
 * 
 * @return true 
 * @return false 
 */
bool Grid::possibleMoves() {
    bool moves = false;
    for (auto &row : grid) {
        for (auto &cell : row) {
            for (auto &nb : cell.getCrossNbs()) {
                moves = checkSwap(cell, *nb);
                if (moves) {
                    observer.notifySuggestion(cell.getLocation(), nb->getLocation());
                    return moves;
                }
            }
        }
    }
    return moves;
}


/**
 * @brief Checks if coordinate is in the grid
 * 
 * @param coord 
 * 
 * @return bool
 * 
 */
bool Grid::inGrid(const Point &coord) const {
    return coord.y >= static_cast<int>(grid.size()) 
            || coord.y < 0 
            || coord.x >= static_cast<int>(grid[0].size())
            || coord.x < 0;
}


/**
 * @brief Checks whether both cells contains the same bomb type
 * 
 * @param c1 
 * @param c2 
 * @return true / false 
 */
bool Grid::sameBomb(Cell &c1, Cell &c2) const {
    auto stripedBomb = [](Component cp) 
        -> bool {return cp == Component::STRIPED_BOMB_H || cp == Component::STRIPED_BOMB_V;};

    return (stripedBomb(c1.type()) && stripedBomb(c2.type()))
        || (c1.type() == Component::WRAPPED_BOMB
        && c2.type() == Component::WRAPPED_BOMB);
}


/**
 * @brief Deduces whether a component is drop-able
 * 
 * @param component
 * 
 * @return bool
 * 
 */
bool Grid::isMobile(Component component) const {
    return !(component == Component::WALL || component == Component::FROSTING2 || component == Component::FROSTING1);
}


/**
 * @brief Verifies if the component can be popped naturally
 * 
 * @param component
 * 
 * @return bool
 * 
 */
bool Grid::canPop(Component component) const {
return !(component == Component::WALL || component == Component::CHERRY 
                                          || component == Component::HAZELNUT
                                          || component == Component::FROSTING2
                                          || component == Component::FROSTING1);
}


/**
 * @brief Checks two cells in a swap to see if the both contain a 
 *  bomb of any type.
 * 
 * @param c1 
 * @param c2 
 * @return true 
 * @return false 
 */
bool Grid::bombSwapCheck(Cell &c1, Cell &c2) const {
    return ((c1.type() != Component::CANDY
            && c2.type() != Component::CANDY) 
            || specialSwapCheck(c1, c2));
}


/**
 * @brief Checks two cells in swap to see if either contains 
 *  a special bomb
 * 
 * @param c1 
 * @param c2 
 * @return bool 
 */
bool Grid::specialSwapCheck(Cell &c1, Cell &c2) const {
     return (canPop(c1.type()) && canPop(c2.type())) 
            && (c1.type() == Component::SPECIAL_BOMB || c2.type() == Component::SPECIAL_BOMB);
}


/**
 * @brief Checks for Wrapped candy bomb spawn condition.
 * 
 * @param cColour 
 * @param direction
 * 
 * @return bool
 * 
 */
int Grid::wrSpawnCond(const std::vector< Cell * > &cColour, Direction direction) const {
    int isWrapped = -1;
    for (int i = 0; i < static_cast<int>(cColour.size()); ++i) {
        ColourNbs cross = continuousColour(*cColour[i]);
        Direction perpendicular = (direction == Direction::HORIZONTAL ? Direction::VERTICAL : Direction::HORIZONTAL);
        if (cross.size(perpendicular) >= 3 && cross.size(perpendicular) < 5) isWrapped = i;
    }
    return isWrapped;
}


/**
 * @brief Returns direction perpendicular to direction given
 * 
 * @param dir 
 * @return Direction 
 */
Direction Grid::perpendicular(Direction dir) const {
    if (dir == Direction::NO_DIRECTION) return dir;
    return dir == Direction::HORIZONTAL ? Direction::VERTICAL : Direction::VERTICAL;
}


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Sets the level
 * 
 * @param level 
 */
void Grid::setLevel(const std::string &level) {

    observer.notifyReset();
    score.reset();

    gd = GameData{FileHandler{level}.getGameData()};
    gameObj.setGameData(gd);

    // Ineffecient order but has to be done for reset for some reason
    completeGrid();
    fileInterpreter();
    clean();
}


/**
 * @brief Attempts swap on grid between two cells and, if the swap is successful, cleans the grid
 * 
 * @param cell1
 * @param cell2
 * 
 */
void Grid::swap(const Point &cell1, const Point &cell2) {
    if (checkSwap(cell1, cell2)) {
        gameObj.swapped();

        exchangeCells(grid[cell1.y][cell1.x], grid[cell2.y][cell2.x]);
        observer.notifySwap(cell1, cell2);

        clean(grid[cell1.y][cell1.x], grid[cell2.y][cell2.x]);
    } 
    else if (isMobile(grid[cell1.y][cell1.x].type()) && isMobile(grid[cell2.y][cell2.x].type()))
        observer.notifyFailedSwap(cell1, cell2);
}