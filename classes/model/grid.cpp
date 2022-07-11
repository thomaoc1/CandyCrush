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
 * @brief Checks for Wrapped Bomb condition on a clear (L, X Shape clear with >=5 candies)
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
 * @brief Checks for striped bomb condition (==4 candy clear)
 * 
 * @param cell
 * @param cColour
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
 * @brief Checks for special bomb condition (==6 candy clear)
 * 
 * @param cell
 * @param cColour
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


/**
 * @brief Checks a cell for every clear condition given a direction to check. Marks all cells
 *  which will be cleared with that cell.
 * 
 * @param cell
 * @param direciton
 * 
 * @return std::vector< Cell * > 
 */
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
    const int colour = initial->getColour();

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
    const int component = rand() % 30;

    // Special Bomb insertion
    //if (component == 0) insert special

    // StripedBomb insertion
    if (component > 0 && component < 3) grid[row][col].setOccupied(std::make_shared<StripedBomb>());

    // Wrapped insertion
    if (component >= 3 && component < 7) grid[row][col].setOccupied(std::make_shared<WrappedBomb>());

    // Wall insertion
    if (component >= 7 && component < 12 && row != 0) grid[row][col].setOccupied(std::make_shared<Wall>());

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
void Grid::insertComponent(Cell * cell, int component) {
    switch (component) {
        case Constants::RED_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::RED));
            break;
        case Constants::BLUE_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::BLUE));
            break;
        case Constants::GREEN_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::GREEN));
            break;
        case Constants::YELLOW_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::YELLOW));
            break;
        case Constants::PURPLE_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::PURPLE));
            break;
        case Constants::ORANGE_STRIPED_BOMB:
            cell->setOccupied(std::make_shared<StripedBomb>(Constants::ORANGE));
            break;        
        case Constants::RED_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::RED));
            break;
        case Constants::BLUE_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::BLUE));
            break;
        case Constants::GREEN_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::GREEN));
            break;
        case Constants::YELLOW_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::YELLOW));
            break;
        case Constants::PURPLE_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::PURPLE));
            break;
        case Constants::ORANGE_WRAPPED_BOMB:
            cell->setOccupied(std::make_shared<WrappedBomb>(Constants::ORANGE));
            break;
        case Constants::WALL:
            cell->setOccupied(std::make_shared<Wall>());
            break;
        default:
            cell->setOccupied(std::make_shared<Candy>(component));
    }
}


void Grid::placeWrappedCandies() {
    for (auto &cell : wrappedBombs) {
        switch (cell.second) {
            case Constants::RED:
                insertComponent(cell.first, Constants::RED_WRAPPED_BOMB);
                break;
            case Constants::BLUE:
                insertComponent(cell.first, Constants::BLUE_WRAPPED_BOMB);
                break;
            case Constants::GREEN:
                insertComponent(cell.first, Constants::GREEN_WRAPPED_BOMB);
                break;
            case Constants::YELLOW:
                insertComponent(cell.first, Constants::YELLOW_WRAPPED_BOMB);
                break;
            case Constants::PURPLE:
                insertComponent(cell.first, Constants::PURPLE_WRAPPED_BOMB);
                break;
            case Constants::ORANGE:
                insertComponent(cell.first, Constants::ORANGE_WRAPPED_BOMB);
                break;
        }  
    }
    wrappedBombs.clear();
}



void Grid::placeStripedCandies() {
    for (auto &cell : stripedBombs) {
        switch (cell.second) {
            case Constants::RED:
                insertComponent(cell.first, Constants::RED_STRIPED_BOMB);
                break;
            case Constants::BLUE:
                insertComponent(cell.first, Constants::BLUE_STRIPED_BOMB);
                break;
            case Constants::GREEN:
                insertComponent(cell.first, Constants::GREEN_STRIPED_BOMB);
                break;
            case Constants::YELLOW:
                insertComponent(cell.first, Constants::YELLOW_STRIPED_BOMB);
                break;
            case Constants::PURPLE:
                insertComponent(cell.first, Constants::PURPLE_STRIPED_BOMB);
                break;
            case Constants::ORANGE:
                insertComponent(cell.first, Constants::ORANGE_STRIPED_BOMB);
                break;
        } 
    }
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
    int delta[3][2] = {{1, -1}, {1, 0}, {1, 1}};
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
                events.addAction(std::make_shared<Drop>(Point{i, j}, Point{i + delta[direction][0], j + delta[direction][1]}));
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
    Cell * c1 = &grid[cell1.y][cell1.x];
    Cell * c2 = &grid[cell2.y][cell2.x];
    if (!(c1->getOccupied() || c2->getOccupied()) 
            || c1->package() == Constants::WALL
            || c2->package() == Constants::WALL) return validity;

    swap(c1, c2);
    std::vector< std::vector< Cell * > > c1_nbs = continuousColour(c1);
    std::vector< std::vector< Cell * > > c2_nbs = continuousColour(c2);

    for (int i = 0; i < 2; ++i) {
        if (c1_nbs[i].size() >= 3 || c2_nbs[i].size() >= 3) validity = true;
    }

    if (!validity) {
        swap(c1, c2);
        std::cout << "Failed to swap " << c1->package() << " and " << c2->package() << std::endl;
    } 
    else {
        events.addAction(std::make_shared<Swap>(cell1, cell2));
        std::cout << "Swapped " << c1->package() << " and " << c2->package() << std::endl; 
    }
    return validity;
}
