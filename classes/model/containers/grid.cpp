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
            observer.notifyInit(coord, cell.type());
        } 
    }
}


/**
 * @brief Interprets files
 * 
 */
void Grid::fileInterpreter() {
    for (auto &ct : gd.components) {
        insertComponent(&grid[ct.first.y][ct.first.x], ct.second);
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
void Grid::wrBombExtract(const std::vector< Cell * > &cColour, int index, int direction) {
    int perpendicular = (direction == Constants::HORIZONTAL ? Constants::VERTICAL : Constants::HORIZONTAL);
    std::vector< Cell * > cross = continuousColour(cColour[index])[perpendicular];
    for (auto &cell : cross) willPop(cell);
    wrappedBombs.push_back({cColour[index], cColour[index]->type()});
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
void Grid::stBombExtract(Cell * cell, int direction) {
    stripedBombs.push_back({cell, {cell->type(), direction}});
}


/**
 * @brief Checks for special bomb condition (==6 candy clear)
 * 
 * @param cell
 * @param cColour
 * 
 * @return bool
 * 
 */
void Grid::spBombExtract(Cell * cell) {
    specialBombs.push_back(cell);
}


/**
 * @brief Extracts required bomb type from parameters given
 * 
 * @param cell 
 * @param cColour
 * @param b
 * 
 */
void Grid::bombExtract(Cell * cell, const std::vector< Cell * > &cColour, const BombInfo &b) {
    enum {Normal, Striped, Wrapped, Special};
    enum {Type, Direction, Index};

    switch (b[Type]) {
            case Striped:
                stBombExtract(cell, b[Direction]);
                break;
            case Wrapped:
                wrBombExtract(cColour, b[Index], b[Direction]);
                break;
            case Special:
                spBombExtract(cell);
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
void Grid::clearCheck(Cell * cell) {

    if (!isOccupied(*cell) || cell->type() == Constants::WALL 
                             || cell->type() == Constants::CHERRY
                             || cell->type() == Constants::HAZELNUT
                             || cell->getPop()) return;

    std::vector< std::vector< Cell * > > contColour = continuousColour(cell);
    if (contColour[Constants::VERTICAL].size() < 3 
        && contColour[Constants::HORIZONTAL].size() < 3) return;
        
    // Else at least 3 consecutives found 
    std::array<int, 2> directions = {Constants::VERTICAL, Constants::HORIZONTAL};
 
    enum {Normal, Striped, Wrapped, Special};
    enum {Type, Direction, Index};
    using BombInfo = std::array<int, 3>;
    BombInfo current = {Normal, Constants::VERTICAL, -1};

    for (auto &dir : directions) {
        /* No combo condition*/
        if (contColour[dir].size() < 3) continue; 
        int index = wrSpawnCond(contColour[dir], dir);
        /* Special Bomb Condition */
        if (current[Type] < Special && spSpawnCond(contColour[dir])) current = {Special, dir, -1};
        /* Wrapped Bomb Condition */
        else if (current[Type] < Wrapped && index >= 0) current = {Wrapped, dir, index};
        /* Striped Bomb Condition */
        else if (current[Type] < Striped && stSpawnCond(contColour[dir])) current = {Striped, dir, -1};
        
        for (auto &c : contColour[dir]) willPop(c);
    }
    bombExtract(cell, contColour[current[Direction]], current);
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
void Grid::wrappedBlast(Cell * target) {
    for (auto &c : target->getNbs()) 
        if (c) willPop(c);
}


/**
 * @brief Simulates wrapped candy explosion
 * 
 * @param target
 * 
 */
void Grid::stripedBlast(Cell * target) {
    if (!isOccupied(*target)) return;

    Point start = target->getLocation();
    std::vector<Cell *> tmp;

    if (target->getBlastDirection() == Constants::VERTICAL) {
        for (int i = start.y + 1; i < ROWS; ++i) tmp.push_back(&grid[i][start.x]);
        for (int i = start.y - 1; i >= 0; --i) tmp.push_back(&grid[i][start.x]);
    }
    else {
        for (int i = start.x + 1; i < COLS; ++i) tmp.push_back(&grid[start.y][i]);
        for (int i = start.x - 1; i >= 0; --i) tmp.push_back(&grid[start.y][i]);
    }

    for (auto &c : tmp) willPop(c);
}



/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 * 
 */
void Grid::unoccupy(Cell * target) {
    target->unOccupy();
    target->popped();
}


void Grid::clearFrostings() {
    std::vector< Cell * > frostings;
    for (auto &cell : toPop) {
        if (cell->type() == Constants::FROSTING1 || cell->type() == Constants::FROSTING2) continue;
        for (auto &nb : cell->getCrossNbs()) {
            if (nb && !nb->getPop() 
                    && (nb->type() == Constants::FROSTING2 || nb->type() == Constants::FROSTING1)) {

                nb->willPop();
                toPop.push_back(nb);
                frostings.push_back(nb);
            }
        }
    }
    for (auto &cell : frostings) cell->popped();
}


/**
 * @brief 
 * 
 */
void Grid::popAll() {
    std::vector<Point> toObserver;
    std::vector< std::pair<Point, int> > filling;

    clearFrostings();

    for (auto &cell : toPop) {
        if (cell->getOccupied()->pop() == Constants::POPPED) {
            if (cell->type() == Constants::FROSTING2) gameObj.frostingPop();
            else gameObj.colourPop(Constants::associatedColour(cell->type()));
            unoccupy(cell);
        }
        else filling.push_back({cell->getLocation(), cell->type()});
        toObserver.push_back(cell->getLocation());

    }
    score.pop(static_cast<int>(toPop.size()));
    observer.notifyPop(toObserver);
    observer.notifyFill(filling);
    toPop.clear();
}


/**
 * @brief
 * 
 */
void Grid::willPop(Cell * target) {
    if (!isOccupied(*target) || !canPop(target->type()) || target->getPop()) return;
    target->willPop();
    toPop.push_back(target);
    if (wrBlastCond(target)) wrappedBlast(target);
    else if (stBlastCond(target)) stripedBlast(target);
}


/**
 * @brief Insert random game component at indices row, col into the Grid
 * 
 * @param row 
 * @param col 
 * 
 */
void Grid::insertComponent(int row, int col) {
    grid[row][col].setOccupied(std::make_shared<Candy>(Constants::randomCandy()));
}


/**
 * @brief Insert specified component onto cell
 * 
 * @param cell
 * @param type
 * @param colour
 * 
 */
void Grid::insertComponent(Cell * cell, int component) {
    switch (component) {
        case Constants::RED:
        case Constants::BLUE:
        case Constants::GREEN:
        case Constants::YELLOW:
        case Constants::PURPLE:
        case Constants::ORANGE:
            cell->setOccupied(std::make_shared<Candy>(component));
            break;
        case Constants::RED_STRIPED_BOMB_V:
        case Constants::BLUE_STRIPED_BOMB_V:
        case Constants::GREEN_STRIPED_BOMB_V:
        case Constants::YELLOW_STRIPED_BOMB_V:
        case Constants::PURPLE_STRIPED_BOMB_V:
        case Constants::ORANGE_STRIPED_BOMB_V:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::associatedColour(component), Constants::VERTICAL));
            break;  
        case Constants::RED_STRIPED_BOMB_H:
        case Constants::BLUE_STRIPED_BOMB_H:
        case Constants::GREEN_STRIPED_BOMB_H:
        case Constants::YELLOW_STRIPED_BOMB_H:
        case Constants::PURPLE_STRIPED_BOMB_H:
        case Constants::ORANGE_STRIPED_BOMB_H:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::associatedColour(component), Constants::HORIZONTAL));
            break;   
        case Constants::RED_WRAPPED_BOMB:
        case Constants::BLUE_WRAPPED_BOMB:
        case Constants::GREEN_WRAPPED_BOMB:
        case Constants::YELLOW_WRAPPED_BOMB:
        case Constants::PURPLE_WRAPPED_BOMB:
        case Constants::ORANGE_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::associatedColour(component)));
            break;
        case Constants::SPECIAL_BOMB:
            cell->setOccupied(std::make_shared<SpecialBomb>());
            break;
        case Constants::WALL:
            cell->setOccupied(std::make_shared<Wall>());
            break;
        case Constants::CHERRY:
            cell->setOccupied(std::make_shared<Cherry>());
            break;
        case Constants::HAZELNUT:
            cell->setOccupied(std::make_shared<Hazelnut>());
            break;
        case Constants::FROSTING1:
            cell->setOccupied(std::make_shared<Frosting>(1));
            break;
        case Constants::FROSTING2:
            cell->setOccupied(std::make_shared<Frosting>(2));
            break;
    }
}


/**
 * @brief Places all wrapped candies from the wrappedBombs array
 * 
 */
void Grid::placeWrappedCandies() {
    for (auto &cell : wrappedBombs) {
        switch (cell.second) {
            case Constants::RED:
                insertComponent(cell.first, Constants::RED_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::RED_WRAPPED_BOMB);
                break;
            case Constants::BLUE:
                insertComponent(cell.first, Constants::BLUE_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::BLUE_WRAPPED_BOMB);
                break;
            case Constants::GREEN:
                insertComponent(cell.first, Constants::GREEN_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::GREEN_WRAPPED_BOMB);
                break;
            case Constants::YELLOW:
                insertComponent(cell.first, Constants::YELLOW_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::YELLOW_WRAPPED_BOMB);
                break;
            case Constants::PURPLE:
                insertComponent(cell.first, Constants::PURPLE_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::PURPLE_WRAPPED_BOMB);
                break;
            case Constants::ORANGE:
                insertComponent(cell.first, Constants::ORANGE_WRAPPED_BOMB);
                observer.notifyInsert(cell.first->getLocation(), Constants::ORANGE_WRAPPED_BOMB);
                break;
        }  
    }

    score.bombSpawn(static_cast<int>(wrappedBombs.size()), Constants::WRAPPED);
    wrappedBombs.clear();
}


/**
 * @brief Places all striped candies from the stripedBombs array
 * 
 */
void Grid::placeStripedCandies() {
    for (auto &cell : stripedBombs) {
        Cell * cp = cell.first;
        int blastDirection = cell.second.second;
        int colour = Constants::associatedColour(cell.second.first);
        int stripedBomb = Constants::colourToSt(colour, blastDirection);
        insertComponent(cp, stripedBomb);
        observer.notifyInsert(cp->getLocation(), stripedBomb);
    }

    score.bombSpawn(static_cast<int>(stripedBombs.size()), Constants::STRIPED);
    stripedBombs.clear();
}


/**
 * @brief
 * 
 */
void Grid::placeSpecialBombs() {
    for (auto &cell : specialBombs) {
        insertComponent(cell, Constants::SPECIAL_BOMB);
        observer.notifyInsert(cell->getLocation(), Constants::SPECIAL_BOMB);
    }
    score.bombSpawn(static_cast<int>(specialBombs.size()), Constants::SPECIAL);
    specialBombs.clear();
}


/**
 * @brief Swaps occupations of two cells
 * 
 * @param c1
 * @param c2
 * 
 */
void Grid::exchangeCells(Cell * c1, Cell * c2) {
    std::shared_ptr<GameComponent> tmp = std::move(c1->getOccupied());
    c1->setOccupied(std::move(c2->getOccupied()));
    c2->setOccupied(std::move(tmp));
}


/**
 * @brief Blast even when one of the elements in a swap is a Special Candy.
 * 
 * @param c1 
 * @param c2 
 */
void Grid::specialBlast(Cell * c1, Cell * c2) {

    if (c1->getBlastType() == Constants::SPECIAL && c2->getBlastType() == Constants::SPECIAL) {
        for (auto &row : grid) 
            for (auto &cell : row) willPop(&cell);
    }
    else {
        Cell * target = c1->getBlastType() == Constants::SPECIAL ? c2 : c1;
        willPop(c1);
        willPop(c2);
        for (auto &row : grid) {
            for (auto &cell : row) {
                if (cell.getColour() != target->getColour()) continue;
                if (target->getBlastType() != Constants::SIMPLE) insertComponent(&cell, target->type());
                willPop(&cell);
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
void Grid::wrStBlast(Cell * c1) {
    Point start = c1->getLocation();
    std::vector< Cell * > tmp;
    for (int i = start.y + 1; i < 9; i += 2) tmp.push_back(&grid[i][start.x]); 
    for (int i = start.y - 1; i >= 0; i -= 2) tmp.push_back(&grid[i][start.x]);
    for (int i = start.x + 1; i < 9; ++i) tmp.push_back(&grid[start.y][i]);
    for (int i = start.x - 1; i >= 0; --i) tmp.push_back(&grid[start.y][i]);
    for (auto &c : tmp) {
        c->setOccupied(std::make_shared<WrappedBomb>(Constants::NONE));
        willPop(c);
        wrappedBlast(c);
    }
}


/**
 * @brief
 * 
 * @param c1
 * @param c2
 * 
 */
void Grid::bombSwap(Cell * c1, Cell * c2) {
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


/*-------------------------------------------------------------------------------------------*
 *                                Grid Manipulation                                          *
 *-------------------------------------------------------------------------------------------*/


/**
 * @brief Fills top row of grid
 * 
 */
bool Grid::fillTop() {
    using CoordColour = std::pair< Point, int >;
    std::vector<CoordColour> toFill;
    for (int i = 0; i < static_cast<int>(grid[0].size()); ++i) {
        if (isOccupied(grid[0][i])) continue;
        insertComponent(0, i);
        toFill.push_back(CoordColour{{i, 0}, grid[0][i].type()});
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
            observer.notifyInit(cell.getLocation(), cell.type());
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
        for (auto &c : row) clearCheck(&c);

    // Pops Cherries and hazels at the bottom
    popIngredient();
    
    if (toPop.size() > 0) {
        clearGrid = false;
        popAll();
        placeWrappedCandies();
        placeStripedCandies();
        placeSpecialBombs();
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
bool Grid::directedDrop(int direction) {
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
            if (direction == Constants::LEFT || direction == Constants::RIGHT) break;   
        }
        if (toDrop.size() > 0 && (direction == Constants::LEFT || direction == Constants::RIGHT)) break;
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
        while(directedDrop(Constants::CENTER));
        // DirectedDrop(Left) -> true : means at least one candy was dropped. !!! So restart DropDown 
        // DirectedDrop(Left) -> false : means no candy was dropped to the left, therefore start DropRight 
        if (!directedDrop(Constants::LEFT)) {
            // DirectedDrop(Right) -> true : means at least candy was dropped. !!! So restart DropDown 
            // DirectedDrop(Right) -> false : means no candy was dropped to the Right, therefore Complete Drop 
            if (!directedDrop(Constants::RIGHT)) dropComplete = true;
        }
    }
}


/**
 * @brief Checks if Cherries or Hazels landed on the lowest row.
 * updates objectives and score. recalls
 * 
 */
void Grid::popIngredient() {
    for (auto &cell : grid[8]){
        if (cell.type() == Constants::CHERRY || cell.type() == Constants::HAZELNUT ) {
            gameObj.ingredientPop();
            cell.willPop();
            toPop.push_back(&cell);
        }
    }
}


/**
 * @brief Combines all grid cleaning mechanics to clean up the grid
 * 
 */
void Grid::clean(Cell * c1, Cell * c2) {
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
    if (gameState() == Constants::WON) FileHandler().dumpScore(score.getScore());
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
    Cell * c1 = &grid[cell1.y][cell1.x];
    Cell * c2 = &grid[cell2.y][cell2.x];
    if (!(isOccupied(*c1) || isOccupied(*c2)) 
            || !isMobile(c1->type())
            || !isMobile(c2->type())) return validity;

    exchangeCells(c1, c2);

    std::vector< std::vector< Cell * > > c1_nbs = continuousColour(c1);
    std::vector< std::vector< Cell * > > c2_nbs = continuousColour(c2);

    validity = c1_nbs[Constants::VERTICAL].size() >= 3 
                || c1_nbs[Constants::HORIZONTAL].size() >= 3
                || c2_nbs[Constants::VERTICAL].size() >= 3
                || c2_nbs[Constants::HORIZONTAL].size() >= 3;

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
std::vector< Cell * > Grid::colourDFS(Cell * initial, int orientation) const {
    // Colour of source
    const int colour = Constants::associatedColour(initial->type());
    // List to save Elligible Candies
    std::vector< Cell * > continousColors = {initial}; 
    // DFS
    std::vector< Cell * > stack = {initial}; 
    Cell * current = initial;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        std::vector< Cell * > nbs = orientation == Constants::VERTICAL ? current->getVertNbs() 
                                                                       : current->getHorizNbs();
        for (auto &nb : nbs) {
            // if  ( find a nb that is different than last nb in list ) OR 
            if (std::find(continousColors.begin(), continousColors.end(), nb) != continousColors.end() 
                || Constants::associatedColour(nb->type()) != colour) continue;
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
std::vector< std::vector< Cell * > > Grid::continuousColour(Cell * initial) const {
    std::vector< std::vector< Cell * > >  ret = {{}, {}};
    if (canPop(initial->type())) {
        std::vector< Cell * > v_cont = colourDFS(initial, Constants::VERTICAL);
        std::vector< Cell * > h_cont = colourDFS(initial, Constants::HORIZONTAL);
        ret = {std::move(v_cont), std::move(h_cont)};
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
                moves = checkSwap(&cell, nb);
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
 * @brief 
 * 
 * @param c1 
 * @param c2 
 * @return true / false 
 */
bool Grid::sameBomb(Cell * c1, Cell * c2) const {
    return (c1->getBlastType() == Constants::STRIPED
        && c2->getBlastType() == Constants::STRIPED)
        || (c1->getBlastType() == Constants::WRAPPED
        && c2->getBlastType() == Constants::WRAPPED);
}


/**
 * @brief Deduces whether a component is drop-able
 * 
 * @param component
 * 
 * @return bool
 * 
 */
bool Grid::isMobile(int component) const {
    return !(component == Constants::WALL || component == Constants::FROSTING2 || component == Constants::FROSTING1);
}


/**
 * @brief
 * 
 * @param component
 * 
 * @return bool
 * 
 */
bool Grid::canPop(int component) const {
return !(component == Constants::WALL || component == Constants::CHERRY 
                                          || component == Constants::HAZELNUT
                                          || component == Constants::FROSTING2
                                          || component == Constants::FROSTING1);
}


/**
 * @brief 
 * 
 * @param c1 
 * @param c2 
 * @return true 
 * @return false 
 */
bool Grid::bombSwapCheck(Cell * c1, Cell * c2) const {
    return ((c1->getBlastType() != Constants::SIMPLE
            && c2->getBlastType() != Constants::SIMPLE) 
            || specialSwapCheck(c1, c2));
}


/**
 * @brief
 * 
 * @param
 * @param
 * 
 * @return bool
 * 
 */
bool Grid::specialSwapCheck(Cell * c1, Cell * c2) const {
     return (canPop(c1->type()) && canPop(c2->type())) 
            && (c1->getBlastType() == Constants::SPECIAL || c2->getBlastType() == Constants::SPECIAL);
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
int Grid::wrSpawnCond(const std::vector< Cell * > &cColour, int direction) const {
    int isWrapped = -1;
    for (int i = 0; i < static_cast<int>(cColour.size()); ++i) {
        std::vector<  std::vector< Cell * > > cross = std::move(continuousColour(cColour[i]));
        int perpendicular = (direction == Constants::HORIZONTAL ? Constants::VERTICAL : Constants::HORIZONTAL);
        if (cross[perpendicular].size() >= 3 && cross[perpendicular].size() < 5) isWrapped = i;
    }
    return isWrapped;
}



/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


Grid::Grid(GridDisplay &observer, const std::string &filename)  
    : observer{observer}, gd{FileHandler{filename}.getGameData()}, gameObj{gd, observer}, score{observer} {

    initialiseCells();
    fileInterpreter();
    completeGrid();

    clean();
}


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

        exchangeCells(&grid[cell1.y][cell1.x], &grid[cell2.y][cell2.x]);
        observer.notifySwap(cell1, cell2);

        clean(&grid[cell1.y][cell1.x], &grid[cell2.y][cell2.x]);
    } 
    else if (isMobile(grid[cell1.y][cell1.x].type()) && isMobile(grid[cell2.y][cell2.x].type()))
        observer.notifyFailedSwap(cell1, cell2);
}