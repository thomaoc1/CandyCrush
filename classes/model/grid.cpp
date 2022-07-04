#include "grid.hpp"


/*-----------------------------------------------------------
 *                                                          *
 *                    Private Methods                       *
 *                                                          *
 -----------------------------------------------------------*/

/**
 * @brief Fills grid
 */
void Grid::fill() {
    for (int i = 0; i < static_cast<int>(grid[0].size()); ++i) {
        if (grid[0][i].getOccupied()) continue;
        insertComponent(0, i);
    }
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
            if (!cell.getOccupied()) continue;
            std::vector< std::vector< Cell * > > contColour = continuousColour(&cell);
            if (contColour[Constants::VERTICAL].size() >= 3) {
                clearGrid = false;
                for (auto &cell : contColour[Constants::VERTICAL]) pop(cell);
            }
            if (contColour[Constants::HORIZONTAL].size() >= 3) {
                clearGrid = false;
                for (auto &cell : contColour[Constants::HORIZONTAL]) pop(cell);
            }
        }
    } 
    return clearGrid;
}


/**
 * @brief Drops all Candies, which have no GameComponent beneath them, by one level. Return true if a candy has been 
 *  dropped and false if not.
 *  DROP ORDER : Middle Left Right
 * 
 * @return bool
 */
void Grid::drop() {
    bool dropComplete = false;
    while (!dropComplete)  {
        std::cout << "=== Drop Down===" << std::endl;
        // Drop down until can't
        while(!dropDown());
        display();


        std::cout << "=== Drop Left===" << std::endl;

        // dropLeft -> false : means at least one candy was dropped. !!! So restart DropDown 
        // dropLeft -> true : means no candy was dropped to the left, therefore start DropRight 
        if (dropLeft()) {
            std::cout << "=== Drop Right===" << std::endl;

            // dropReft -> false : means at least candy was dropped. !!! So restart DropDown 
            // dropReft -> true : means no candy was dropped to the Right, therefore Complete Drop 

            if (dropRight()) dropComplete = true;
        }
        display();
    }
}



bool Grid::dropDown() {
    bool allDropped = true;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(grid[0].size()) - 1; j >= 0; --j) {
            Cell &cell = grid[i][j];
            if (!cell.getOccupied() || cell.package() == Constants::WALL) continue;
            Cell * cellBeneath = cell.getBelow(); 
            if (cellBeneath && !cellBeneath->getOccupied()) {
                cellBeneath->setOccupied(cell.getOccupied());
                cell.unOccupy();
                allDropped = false;  
            }
        }
    }
    return allDropped;
}


bool Grid::dropLeft() {
    bool allDropped = true;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(grid[0].size()) - 1; j >= 0; --j) {
            Cell &cell = grid[i][j]; 
            if (!cell.getOccupied() || cell.package() == Constants::WALL) continue;   
            Cell * cellBeneathLeft = cell.getBelowLeft();   
            // Cell directly belowLeft
            if (cellBeneathLeft && !cellBeneathLeft->getOccupied()) {
                cellBeneathLeft->setOccupied(cell.getOccupied());
                cell.unOccupy();
                allDropped = false; 
                break;   
            }
        }
        if (!allDropped) break;
    }
    
    return allDropped;

}


bool Grid::dropRight() {
    bool allDropped = true;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        for (int j = static_cast<int>(grid[0].size()) - 1; j >= 0; --j) {
            Cell &cell = grid[i][j];
            if (!cell.getOccupied() || cell.package() == Constants::WALL) continue;
            // Cell below right
            Cell * cellBeneathRight = cell.getBelowRight();
            if (cellBeneathRight && !cellBeneathRight->getOccupied()) {
                cellBeneathRight->setOccupied(cell.getOccupied());
                cell.unOccupy();
                allDropped = false;   
                break; 
            }
        }
        if (!allDropped) break;
    }
    return allDropped;
}




/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 */
void Grid::pop(Cell * target) {
    target->unOccupy();
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
    const char colour = initial->package().back();

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
                || nb->package().back() != colour) continue;
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
std::vector< std::vector< Cell * > >  Grid::continuousColour(Cell * initial) {
    // Fetching sequential same coloured neighbours
    std::vector< Cell * > v_cont = colourDFS(initial, Constants::VERTICAL);
    std::vector< Cell * > h_cont = colourDFS(initial, Constants::HORIZONTAL);
    std::vector< std::vector< Cell * > >  ret{std::move(v_cont), std::move(h_cont)};
    return ret;
}


/*-----------------------------------------------------------
 *                                                          *
 *                    Public Methods                        *
 *                                                          *
 -----------------------------------------------------------*/


Grid::Grid() {
    // Initialising board with Cells and GameComponents
    // 0 1 2 3 4 5 ...
    // 1 X X X X X
    // 2 X X X X X 
    // ...

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
 * @brief Cleans up grid by popping all elligible candies and dropping. This process is repeated
 *  until there are no candies to pop. 
 */
void Grid::clean() {
    while(!clear()) {
        std::cout << "=== Clear ===" << std::endl;
        display();
        std::cout << "=== Drop ===" << std::endl;
        drop();
        display();
        std::cout << "=== Fill ===" << std::endl;
        fill();
        display();
        
    }  
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


/**
 * @brief Temporary method for displaying board
 * 
 */
void Grid::display() const {
    std::vector< std::vector< std::string > > tmp = package();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (tmp[row][col].length() == 1) std::cout << tmp[row][col] + "   ";
            else std::cout << tmp[row][col] + " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n"; 

    // std::cout << grid[0][0].getBelowRight() << std::endl;
}
