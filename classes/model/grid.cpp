#include "grid.hpp"

/***************************
 * PIVATE METHODS
 ***************************/


/**
 * @brief 'Pops' the Candy occupying the cell by Un-occupying it 
 * 
 * @param target
 */
void Grid::pop(Cell * target) {
    target->unOccupy();
}

/**
 * @brief Insert random game component at indices row, col
 * 
 * @param row 
 * @param col 
 */
void Grid::insertComponent(int row, int col) {
    const int component = rand() % 10;

    // Wall insertion
    if (component == 7) grid[row][col].setOccupied(std::make_shared<Wall>());

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
 * @return std::pair<std::vector< Cell * >, std::vector< Cell * > >
 */
std::pair<std::vector< Cell * >, std::vector< Cell * > > Grid::getNeighbours(int row, int col) {

    // Possible shifts
    const std::vector<int> DELTA = {-1, 1};
    
    std::vector< Cell * > verticalNbs;
    std::vector< Cell * > horizontalNbs;    
    std::pair< std::vector< Cell * >, std::vector< Cell * > > neighbours;
    
    for (auto &d : DELTA) {
        int row_d = row + d;
        int col_d = col + d;

        // Validity of vertical shift
        if (! (row_d >= static_cast<int>(grid[0].size()) 
            || row_d < 0)) {
                verticalNbs.push_back(&grid[row_d][col]);
                if (d == 1) grid[row][col].setBelow(&grid[row_d][col]);
            }
        
        // Validity of horizontal shift
        if (! (col_d >= static_cast<int>(grid.size())
            || col_d < 0 )) {
                horizontalNbs.push_back(&grid[row][col_d]);
            }
    }
    
    neighbours.first = std::move(verticalNbs);
    neighbours.second = std::move(horizontalNbs);

    return neighbours;
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
    const char colour = initial->package().back();
    enum ori{vertical, horizontal};
    std::vector< Cell * > stack = {initial}; 
    std::vector< Cell * > continousColors = {initial}; 
    Cell * current = initial;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        std::vector< Cell * > nbs;
        if (orientation == vertical) nbs = current->getVertNbs();
        else nbs = current->getHorizNbs();
        for (auto &nb : nbs) {
            if (std::find(continousColors.begin(), continousColors.end(), nb) != continousColors.end() 
                || nb->package().back() != colour) continue;
            stack.push_back(nb);
            continousColors.push_back(nb);
        }
    }
    return continousColors;
}


/**
 * @brief Returns vertical and horizontal continuous neighbours which have the same colour as 
 *  the GameComponent on the initial Cell.
 * 
 * @param initial
 * @return std::pair<std::vector< Cell * >, std::vector< Cell * > >
 */
std::pair<std::vector< Cell * >, std::vector< Cell * > > Grid::continuousColour(Cell * initial) {
    enum orientation{vertical, horizontal};
    std::vector< Cell * > v_cont = colourDFS(initial, vertical);
    std::vector< Cell * > h_cont = colourDFS(initial, horizontal);
    std::pair<std::vector< Cell * >, std::vector< Cell * > > ret;
    ret.first = std::move(v_cont);
    ret.second = std::move(h_cont);
    return ret;
}

/***************************
 * PUBLIC METHODS
 ***************************/
Grid::Grid() {

    // Initialising board with Cells and GameComponents
    for (int row = 0; row < 9; ++row) {
        grid.push_back(std::vector<Cell>(9));
        for (int col = 0; col < 9; ++col) {
            if (col == 0 && row == 0) continue;
            insertComponent(row, col);
        }
    }

    // Setting neighbours of each Cell
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::vector< std::vector< Cell * > > nbs = getNeighbours(row, col);

            grid[row][col].setVertNbs(nbs[Constants::VERTICAL]);
            grid[row][col].setHorizNbs(nbs[Constants::HORIZONTAL]);
        }
    }
}


/**
 * @brief Cleans up grid by popping all elligible candies and dropping. This process is repeated
 *  until there are no candies to pop. 
 */
void Grid::clean() {
    while(!clear()) {
        // std::cout << "=== Clear ===" << std::endl;
        // display();
        while(!drop());
        // std::cout << "=== Drop ===" << std::endl;
        // display();
    }  
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
 * 
 * @return bool
 */
bool Grid::drop() {
    bool allDropped = true;
    for (auto &row : grid) {
        for (auto &cell : row) {
            Cell * cellBeneath = cell.getBelow();
            if (!(cell.getOccupied() && cell.package() != Constants::WALL
                    && cellBeneath && !cellBeneath->getOccupied())) continue;
            
            cellBeneath->setOccupied(cell.getOccupied());
            cell.unOccupy();
            allDropped = false;
        }
    }
    return allDropped;
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
void Grid::display()  {
    std::vector< std::vector< std::string > > tmp = package();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (tmp[row][col].length() == 1) std::cout << tmp[row][col] + "   ";
            else std::cout << tmp[row][col] + " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n"; 

    // std::cout << grid[8][1].getBelow()->package() << std::endl;
}
