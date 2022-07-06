#include "grid.hpp"


/*-----------------------------------------------------------
 *                                                          *
 *                    Private Methods                       *
 *                                                          *
 -----------------------------------------------------------*/


/*-----------------------------------------------------------
 *                                                          *
 *           Grid Cleaning: Colour popping                  *
 *                                                          *
 -----------------------------------------------------------*/


/**
 * @brief Given 
 * 
 * @param cColour
 * @param direction
 * 
 * @return bool
 */
bool Grid::wrappedBomb(const std::vector< Cell * > &cColour, int direction) {
    bool isWrapped = false;
    for (auto &cell : cColour) {
        std::vector< std::vector< Cell * > > cross = continuousColour(cell);
        int perpendicular = (direction == Constants::HORIZONTAL ? Constants::VERTICAL : Constants::HORIZONTAL);
        if (cross[perpendicular].size() >= 3) {
            isWrapped = true;
            wrappedBombs.push_back({cell, cell->package()});
            for (auto &pCell : cross[perpendicular]) {
                pCell->willPop();
                toPop.push_back(pCell);
            }
        }
        cell->willPop();
        toPop.push_back(cell);
    }
    return isWrapped;
}


/**
 * @brief
 * 
 * @param
 * @param
 * 
 * @return bool
 */
bool Grid::stripedBomb(Cell * cell, const std::vector< Cell * > &cColour) {
    bool isStriped = false;
    if (cColour.size() == 4) {
        stripedBombs.push_back({cell, cell->package()});
        isStriped = true;
    }
    for (auto &cell : cColour) {
        cell->willPop();
        toPop.push_back(cell);
    }
    return isStriped;
}


/**
 * @brief
 * 
 * @param
 * @param
 * 
 * @return bool
 */
bool Grid::specialBomb(Cell * cell, const std::vector< Cell * > &cColour) {
    bool isSpecial = false;
    if (cColour.size() == 6) {
        specialBombs.push_back(cell);
        isSpecial = true;
    }
    for (auto &cell : cColour) {
        cell->willPop();
        toPop.push_back(cell);
    } 
    return isSpecial;
}


std::vector< Cell * > Grid::clearCheck(Cell * cell, int direction) {
    if (!cell->getOccupied() || cell->getPop()) return std::vector< Cell * >();
    std::vector< std::vector< Cell * > > contColour = continuousColour(cell);
    if (contColour[direction].size() >= 3) {
        /* Special Bomb Condition */
        specialBomb(cell, contColour[direction]);
        /* Wrapped Bomb Condition */
        wrappedBomb(contColour[direction], direction);
        /* Striped Bomb Condition */
        stripedBomb(cell, contColour[direction]) ;   
    }
    return toPop;
}


/**
 * @brief Returns continous Candy neighbours with identical colour as the source Candy on the initial cell
 *  in the given orientation.
 * 
 * @param initial 
 * @param orientation
 * @return std::vector< Cell * > 
 */
std::vector< Cell * > Grid::colourDFS(Cell * initial, int orientation) const {
    // Colour of source
    const std::string colour = initial->getColour();

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
                || nb->getColour() != colour) continue;
            // Elligible Candies
            stack.push_back(nb);
            continousColors.push_back(nb);
        }
    }
    return continousColors;
}


/**
 * @brief Returns vertical and horizontal sequential neighbours which have the same colour as 
 *  the GameComponent on the initial Cell.
 * 
 * @param initial
 * @return std::vector< std::vector< Cell * > >
 */
std::vector< std::vector< Cell * > > Grid::continuousColour(Cell * initial) {
    // Fetching sequential same coloured neighbours
    std::vector< Cell * > v_cont = colourDFS(initial, Constants::VERTICAL);
    std::vector< Cell * > h_cont = colourDFS(initial, Constants::HORIZONTAL);
    std::vector< std::vector< Cell * > >  ret{std::move(v_cont), std::move(h_cont)};
    return ret;
}


/*-----------------------------------------------------------
 *                                                          *
 *               Insertion / Supression                     *
 *                                                          *
 -----------------------------------------------------------*/


/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 */
void Grid::pop(Cell * target) {
    target->unOccupy();
    target->popped();
}


/**
 * @brief Pops all cells in toPop vector
 */
void Grid::popAll() {
    for (auto &cell : toPop) pop(cell);
    toPop.clear();
}


/**
 * @brief Insert random game component at indices row, col into the Grid
 * 
 * @param row 
 * @param col 
 */
void Grid::insertComponent(int row, int col) {
    const int component = rand() % 10;

    // Wall insertion
    if (component == 7 && row != 0) grid[row][col].setOccupied(std::make_shared<Wall>());

    // CandyBomb insertion
    else if (component == 8) grid[row][col].setOccupied(std::make_shared<CandyBomb>());

    // Special Bomb insertion
    //else if (component == 9) board[row][col].setOccupied(nullptr);

    // Candy insertion
    else grid[row][col].setOccupied(std::make_shared<Candy>());
}


/**
 * @brief Insert specified component onto cell
 * 
 * @param cell
 * @param type
 * @param colour
 */
void Grid::insertComponent(Cell * cell, const std::string type, const std::string &colour) {
    if (type == Constants::BOMB) cell->setOccupied(std::make_shared<CandyBomb>(colour));
    // ...
}


void Grid::placeWrappedCandies() {
    for (auto &cell : wrappedBombs) insertComponent(cell.first, Constants::BOMB, cell.second);
    wrappedBombs.clear();
}


void Grid::placeStripedCandies() {
    for (auto &cell : stripedBombs) insertComponent(cell.first, Constants::BOMB, cell.second);
    stripedBombs.clear();
}


/**
 * @brief Swaps occupations of two cells
 * 
 * @param c1
 * @param c2
 */
void Grid::swap(Cell * c1, Cell * c2) {
    std::shared_ptr<GameComponent> tmp = std::move(c1->getOccupied());
    c1->setOccupied(std::move(c2->getOccupied()));
    c2->setOccupied(std::move(tmp));
}


/*-----------------------------------------------------------
 *                                                          *
 *                Neighbour Fetching                        *
 *                                                          *
 -----------------------------------------------------------*/


/**
 * @brief Returns vertical and horizontal neighbours of game component at row, col as
 *  a pair of vectors
 * 
 * @param row 
 * @param col 
 * @return std::vector< std::vector< Cell * > >
 */
std::vector< std::vector< Cell * > > Grid::getCrossNbs(int row, int col) {

    // Possible shifts
    const std::vector<int> DELTA = {-1, 1};
    
    std::vector< Cell * > verticalNbs;
    std::vector< Cell * > horizontalNbs;    
    
    
    for (auto &d : DELTA) {
        int row_d = row + d;
        int col_d = col + d;

        // Validity of vertical shift
        if (! (row_d >= static_cast<int>(grid[0].size()) 
            || row_d < 0)) {
                verticalNbs.push_back(&grid[row_d][col]);
                
            }
        
        // Validity of horizontal shift
        if (! (col_d >= static_cast<int>(grid.size())
            || col_d < 0 )) {
                horizontalNbs.push_back(&grid[row][col_d]);
            }
    }
    
    std::vector< std::vector< Cell * > > neighbours{std::move(verticalNbs), std::move(horizontalNbs)};

    return neighbours;
}

/**
 * @brief
 */
std::vector< Cell * > Grid::getBelowNbs(int row, int col) {
    std::vector< Cell * > nbs{nullptr, nullptr, nullptr}; 

    const std::vector<Point> DELTA = {{1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < static_cast<int>(DELTA.size()); ++i) {
        int row_d = row + DELTA[i].x;
        int col_d = col + DELTA[i].y;

        if (row_d >= static_cast<int>(grid.size()) 
            || row_d < 0 
            || col_d >= static_cast<int>(grid[0].size())
            || col_d < 0) continue;

        nbs[i] = &grid[row_d][col_d];
    }    
    return nbs;            
}


/*-----------------------------------------------------------
 *                                                          *
 *                    Public Methods                        *
 *                                                          *
 -----------------------------------------------------------*/


Grid::Grid() {
    for (int row = 0; row < 9; ++row) {
        grid.push_back(std::vector<Cell>(9));
        for (int col = 0; col < 9; ++col) {
            insertComponent(row, col);
        }
    }
    // Setting neighbours of each Cell
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::vector< std::vector< Cell * > > xNbs = getCrossNbs(row, col);
            std::vector< Cell * > belowNbs = getBelowNbs(row, col);

            grid[row][col].setBelowLeft(belowNbs[Constants::BELOW_LEFT]);
            grid[row][col].setBelow(belowNbs[Constants::BELOW]);
            grid[row][col].setBelowRight(belowNbs[Constants::BELOW_RIGHT]);
            
            grid[row][col].setVertNbs(xNbs[Constants::VERTICAL]);
            grid[row][col].setHorizNbs(xNbs[Constants::HORIZONTAL]);
        }
    }
}


/*-----------------------------------------------------------
 *                                                          *
 *                      Grid Cleaning                       *
 *                                                          *
 -----------------------------------------------------------*/


/**
 * @brief Fills grid
 */
bool Grid::fill() {
    bool filled = false;
    for (int i = 0; i < static_cast<int>(grid[0].size()); ++i) {
        if (grid[0][i].getOccupied()) continue;
        insertComponent(0, i);
        filled = true;
    }
    return filled;
}   


/**
 * @brief Pops all continuous, same coloured Candies. Returns true if a pop has been performed and 
 *  false if not.
 *
 * @return bool 
 */
bool Grid::clear() {
    bool clearGrid = true;
    for (auto &row : grid) {
        for (auto &cell : row) {
            clearCheck(&cell, Constants::HORIZONTAL);
            clearCheck(&cell, Constants::VERTICAL);
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
 */
bool Grid::directedDrop(int direction) {
    bool drop = false;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(grid[0].size()) - 1; j >= 0; --j) {
            Cell &cell = grid[i][j]; 
            if (!cell.getOccupied() || cell.package() == Constants::WALL) continue;   

            Cell * cellBeneath = cell.getBelow(direction);

            if (cellBeneath && !cellBeneath->getOccupied()) {
                cellBeneath->setOccupied(cell.getOccupied());
                cell.unOccupy();
                drop = true; 
                if (direction == Constants::BELOW_LEFT || direction == Constants::BELOW_RIGHT) break;   
            }
        }
        if (drop && (direction == Constants::BELOW_LEFT || direction == Constants::BELOW_RIGHT)) break;
    }
    return drop;
}


/**
 * @brief Verifies validity of a Candy swap. If valid, executes swap.
 * 
 * @param cell1
 * @param cell2
 * @return bool
 */
bool Grid::checkSwap(const Point &cell1, const Point &cell2) {
    bool validity = false;
    Cell * c1 = &grid[cell1.x][cell1.y];
    Cell * c2 = &grid[cell2.x][cell2.y];
    if (!(c1->getOccupied() || c2->getOccupied()) 
            || c1->package() == Constants::WALL
            || c2->package() == Constants::WALL) return validity;

    swap(c1, c2);
    std::vector< std::vector< Cell * > > c1_nbs = continuousColour(c1);
    std::vector< std::vector< Cell * > > c2_nbs = continuousColour(c2);

    for (int i = 0; i < 2; ++i) {
        if (c1_nbs[i].size() >= 3 || c2_nbs[i].size() >= 3) validity = true;
    }

    if (!validity) swap(c1, c2);

    return validity;
}


/**
 * @brief Packages the board in to a vector of strings
 * 
 * @return std::vector< std::vector< std::string > > 
 */
std::vector< std::vector< std::string > > Grid::package() const {
    std::vector< std::vector< std::string > > packagedBoard;
    for (int row = 0; row < 9; ++row) {
        packagedBoard.push_back({});
        for (int col = 0; col < 9; ++col) {
            packagedBoard[row].push_back(grid[row][col].package());
        }
    }
    return packagedBoard;
}