#include "grid.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Private Methods                                     *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


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
bool Grid::wrappedBomb(const std::vector< Cell * > &cColour, int direction) {
    bool isWrapped = false;
    for (auto &cell : cColour) {
        std::vector< std::vector< Cell * > > cross = continuousColour(cell);
        int perpendicular = (direction == Constants::HORIZONTAL ? Constants::VERTICAL : Constants::HORIZONTAL);
        if (cross[perpendicular].size() >= 3) {
            isWrapped = true;
            wrappedBombs.push_back({cell, cell->type()});
            for (auto &pCell : cross[perpendicular]) {
                pCell->willPop();
                toPop.push_back(pCell);
            }
        }
    }
    return isWrapped;
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
bool Grid::stripedBomb(Cell * cell, const std::vector< Cell * > &cColour, int direction) {
    bool isStriped = false;
    if (cColour.size() == 4) {
        stripedBombs.push_back({cell, {cell->type(), direction}});
        isStriped = true;
    }
    return isStriped;
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
bool Grid::specialBomb(Cell * cell, const std::vector< Cell * > &cColour) {
    bool isSpecial = false;
    if (cColour.size() == 6) {
        specialBombs.push_back(cell);
        isSpecial = true;
    }
    return isSpecial;
}


/**
 * @brief Checks a cell for every clear condition given a direction to check. Marks all cells
 *  which will be cleared with that cell.
 * 
 * @param cell
 * @param direciton
 * 
 */
void Grid::clearCheck(Cell * cell, int direction) {
    if (!cell->getOccupied() || cell->getPop()) return;
    std::vector< std::vector< Cell * > > contColour = continuousColour(cell);
    if (contColour[direction].size() < 3) return;  
    /* Special Bomb Condition */
    specialBomb(cell, contColour[direction]);
    /* Wrapped Bomb Condition */
    wrappedBomb(contColour[direction], direction);
    /* Striped Bomb Condition */
    stripedBomb(cell, contColour[direction], direction);   

    for (auto &c : contColour[direction]) {
        c->willPop();
        toPop.push_back(c);
        if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
        else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);           
    }
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
    for (auto &c : target->getNbs()) {
        if (!c || c->getPop()) continue;
        c->willPop();
        toPop.push_back(c);
        if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
        else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);
    }
}


/**
 * @brief Simulates wrapped candy explosion
 * 
 * @param target
 * 
 */
void Grid::stripedBlast(Cell * target) {
    int direction = target->getOccupied()->getBlastDirection();
    Point start = target->getLocation();
    Cell * c;
    if (direction == Constants::VERTICAL) {
        for (int i = start.y + 1; i < 9; ++i){
            c = &grid[i][start.x];
            toPop.push_back(c);
            c->willPop();
            if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
            else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);
        }
        for (int i = start.y - 1; i >= 0; --i){
            c = &grid[i][start.x];
            toPop.push_back(c);
            c->willPop();
            if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
            else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);
        }
    }
    else {
        for (int i = start.x + 1; i < 9; ++i){
            c = &grid[start.y][i];
            toPop.push_back(c);
            c->willPop();
            if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
            else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);
        }
        for (int i = start.x - 1; i >= 0; --i){
            c = &grid[start.y][i];
            toPop.push_back(c);
            c->willPop();
            if (c->getOccupied()->getBlastArea() == 9) wrappedBlast(c);
            else if (c->getOccupied()->getBlastDirection() != Constants::NO_DIRECTION) stripedBlast(c);
        }
    }
}



/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 * 
 */
void Grid::pop(Cell * target) {
    target->unOccupy();
    target->popped();
}


/**
 * @brief Pops all cells in toPop vector
 * 
 */
void Grid::popAll() {
    std::vector<Point> toObserver;
    for (auto &cell : toPop) {
        pop(cell);
        toObserver.push_back(cell->getLocation());
    }
    observer->notifyPop(toObserver);
    toPop.clear();
}


/**
 * @brief Insert random game component at indices row, col into the Grid
 * 
 * @param row 
 * @param col 
 * 
 */
void Grid::insertComponent(int row, int col) {
    const int component = rand() % 81;
    // StripedBomb insertion
    if (component > 0 && component < 3) grid[row][col].setOccupied(std::make_shared<StripedBomb>());
    // Wrapped insertion
    if (component >= 3 && component < 7) grid[row][col].setOccupied(std::make_shared<WrappedBomb>());
    // Wall insertion
    //if (component >= 7 && component < 9 && row != 0) grid[row][col].setOccupied(std::make_shared<Wall>());
    // Candy insertion
    else grid[row][col].setOccupied(std::make_shared<Candy>());
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
        case Constants::WALL:
            cell->setOccupied(std::make_shared<Wall>());
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
                observer->notifyInsert(cell.first->getLocation(), Constants::RED_WRAPPED_BOMB);
                break;
            case Constants::BLUE:
                insertComponent(cell.first, Constants::BLUE_WRAPPED_BOMB);
                observer->notifyInsert(cell.first->getLocation(), Constants::BLUE_WRAPPED_BOMB);
                break;
            case Constants::GREEN:
                insertComponent(cell.first, Constants::GREEN_WRAPPED_BOMB);
                observer->notifyInsert(cell.first->getLocation(), Constants::GREEN_WRAPPED_BOMB);
                break;
            case Constants::YELLOW:
                insertComponent(cell.first, Constants::YELLOW_WRAPPED_BOMB);
                observer->notifyInsert(cell.first->getLocation(), Constants::YELLOW_WRAPPED_BOMB);
                break;
            case Constants::PURPLE:
                insertComponent(cell.first, Constants::PURPLE_WRAPPED_BOMB);
                observer->notifyInsert(cell.first->getLocation(), Constants::PURPLE_WRAPPED_BOMB);
                break;
            case Constants::ORANGE:
                insertComponent(cell.first, Constants::ORANGE_WRAPPED_BOMB);
                observer->notifyInsert(cell.first->getLocation(), Constants::ORANGE_WRAPPED_BOMB);
                break;
        }  
    }
    wrappedBombs.clear();
}


/**
 * @brief Places all striped candies from the stripedBombs array
 * 
 */
void Grid::placeStripedCandies() {
    for (auto &cell : stripedBombs) {
        Cell * cp = cell.first;
        int blastDirection = cell.second.second, colour = cell.second.first;

        int stripedBomb = Constants::associatedStripedBomb(colour, blastDirection);
        insertComponent(cp, stripedBomb);
        observer->notifyInsert(cp->getLocation(), stripedBomb);
    }
    stripedBombs.clear();
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
        if (grid[0][i].getOccupied()) continue;
        insertComponent(0, i);
        toFill.push_back(CoordColour{{i, 0}, grid[0][i].type()});
    }
    if (toFill.size() > 0) observer->notifyFill(toFill);
    return toFill.size() > 0;
}   


/**
 * @brief Repeatedly fills the top row
 * 
 */
void Grid::completeFill() {
    while(fillTop()) {
        std::cout << "====== Fill ========" << std::endl;
        //displayTerminal();
        completeDrop();
    }
}


/**
 * @brief Pops all continuous, same coloured Candies. Returns true if a pop has been performed and 
 *  false if not.
 *
 * @return bool 
 * 
 */
bool Grid::clear() {
    bool clearGrid = true;
    for (auto &row : grid) {
        for (auto &c : row) {
            clearCheck(&c, Constants::HORIZONTAL);
            clearCheck(&c, Constants::VERTICAL);
        }
    } 
    if (toPop.size() > 0) clearGrid = false;
    popAll();
    placeWrappedCandies();
    placeStripedCandies();
    return clearGrid;
}


/**
 * @brief Drop GameComponent in given direction if possible. If a candy has been dropped, returns true.
 * 
 * @param direction
 * @return bool
 * 
 */
bool Grid::directedDrop(int direction) {
    std::vector<Point> toDrop;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(grid[0].size()) - 1; j >= 0; --j) {
            Cell &cell = grid[i][j]; 
            if (!cell.getOccupied() || cell.type() == Constants::WALL) continue;   

            Cell * cellBeneath = cell.getBelow(direction);

            if (cellBeneath && !cellBeneath->getOccupied()) {
                cellBeneath->setOccupied(cell.getOccupied());
                cell.unOccupy();
                toDrop.push_back(cell.getLocation());
                if (direction == Constants::LEFT || direction == Constants::RIGHT) break;   
            }
        }
        if (toDrop.size() > 0 && (direction == Constants::LEFT || direction == Constants::RIGHT)) break;
    }
    if (toDrop.size() > 0) {
        observer->notifyDrop(toDrop, direction);
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
        while(directedDrop(Constants::CENTER)) {
            std::cout << "=== Drop Down ===" << std::endl;
            //displayTerminal();
        }
        // DirectedDrop(Left) -> true : means at least one candy was dropped. !!! So restart DropDown 
        // DirectedDrop(Left) -> false : means no candy was dropped to the left, therefore start DropRight 
        if (!directedDrop(Constants::LEFT)) {
            // DirectedDrop(Right) -> true : means at least candy was dropped. !!! So restart DropDown 
            // DirectedDrop(Right) -> false : means no candy was dropped to the Right, therefore Complete Drop 
            if (!directedDrop(Constants::RIGHT)) dropComplete = true;
            else {
                std::cout << "=== Drop Right ===" << std::endl;
                //displayTerminal();
            }
    
        } 
        else {
            std::cout << "=== Drop Left ===" << std::endl;
            //displayTerminal();
        }
    }
}


/**
 * @brief Combines all grid cleaning mechanics to clean up the grid
 * 
 */
void Grid::clean() {
    //displayTerminal();
    while (!clear()) {
        std::cout << "=== Clear ===" << std::endl;

        //displayTerminal();

        completeDrop();
        completeFill();
    } 
}


/**
 * @brief Verifies validity of a Candy swap. If valid, executes swap.
 * 
 * @param cell1
 * @param cell2
 * @return bool
 * 
 */
bool Grid::checkSwap(const Point &cell1, const Point &cell2) {
    bool validity = false;
    Cell * c1 = &grid[cell1.y][cell1.x];
    Cell * c2 = &grid[cell2.y][cell2.x];
    if (!(c1->getOccupied() || c2->getOccupied()) 
            || c1->type() == Constants::WALL
            || c2->type() == Constants::WALL) return validity;

    exchangeCells(c1, c2);

    std::vector< std::vector< Cell * > > c1_nbs = continuousColour(c1);
    std::vector< std::vector< Cell * > > c2_nbs = continuousColour(c2);

    for (int i = 0; i < 2; ++i) {
        if (c1_nbs[i].size() >= 3 || c2_nbs[i].size() >= 3) validity = true;
    }

    if (!validity) exchangeCells(c1, c2);

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
 * @return std::vector< Cell * > 
 * 
 */
std::vector< Cell * > Grid::colourDFS(Cell * initial, int orientation) const {
    // Colour of source
    const int colour = Constants::associatedColour(initial->type());
    // DFS Tools
    std::vector< Cell * > stack = {initial}; 
    Cell * current = initial;
    // Elligible Candies
    std::vector< Cell * > continousColors = {initial}; 
    // DFS
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        std::vector< Cell * > nbs;
        if (orientation == Constants::VERTICAL) nbs = current->getVertNbs();
        else nbs = current->getHorizNbs();
        for (auto &nb : nbs) {
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
std::vector< std::vector< Cell * > > Grid::continuousColour(Cell * initial) {
    // Fetching sequential same coloured neighbours
    std::vector< Cell * > v_cont = colourDFS(initial, Constants::VERTICAL);
    std::vector< Cell * > h_cont = colourDFS(initial, Constants::HORIZONTAL);
    std::vector< std::vector< Cell * > >  ret{std::move(v_cont), std::move(h_cont)};
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
 *                                           Utility                                         *
 *-------------------------------------------------------------------------------------------*/


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



/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


Grid::Grid(std::shared_ptr<GridDisplay> observer, const std::string &level)  : observer{observer} {
    for (int row = 0; row < 9; ++row) {
        std::vector<Cell> tmp = {};
        for (int col = 0; col < 9; ++col) {
            tmp.emplace_back(Cell(row, col));
        }
        grid.emplace_back(std::move(tmp));
    }

    GameData gd = FileHandler{level}.getGameData();

    for (auto &p : gd.walls) insertComponent(&grid[p.y][p.x], Constants::WALL);
    // for (auto &p : gd.frostings);
    
    for (auto &row : grid) {
        for (auto &cell : row) {
            Point coord = cell.getLocation();
            cell.setNbs(getNbs(coord.y, coord.x));
            if(!cell.getOccupied()) insertComponent(coord.y, coord.x);
            observer->notifyInit(coord, cell.type());
        } 
    }

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
    std::cout << "swap call" << std::endl;
    if (checkSwap(cell1, cell2)) {
        observer->notifySwap(cell1, cell2);
        clean();
    } 
    // else observer->notifyFailedSwap(cell1, cell2);
}



void Grid::displayTerminal() const {
    std::cout << "\n               GRID\n=================================\n";
    for (auto &r : grid) {
        for (auto &c : r) {
            if (c.type() > 9) std::cout << c.type() << "  ";
            else std::cout << (c.type() == 8 ? -1 : c.type()) << "   ";
        }
        std::cout << "\n";
    }
}