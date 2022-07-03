#include "grid.hpp"

/***************************
 * PIVATE METHODS
 ***************************/

/**
 * @brief Insert random game component at indices row, col
 * 
 * @param row 
 * @param col 
 */
void Grid::insertComponent(int row, int col) {
    int component = rand() % 10;

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
 * @brief Returns neighbours of game component at row, col
 * 
 * @param row 
 * @param col 
 * @return std::vector< std::shared_ptr<Cell> > 
 */
std::vector< Cell * > Grid::getNeighbours(int row, int col) {

    // Possible shifts
    std::vector< std::pair<int,int> > DELTA {{ 1, 0}, 
                                             { 0, 1}, 
                                             {-1, 0}, 
                                             { 0,-1}};
    
    std::vector< Cell * > neighbours;
    
    for (auto &d : DELTA) {
        int row_d = row + d.first;
        int col_d = col + d.second;

        // Validity of shft
        if (row_d >= static_cast<int>(grid[0].size()) 
            || row_d < 0
            || col_d >= static_cast<int>(grid.size())
            || col_d < 0 ) continue;
        
        neighbours.push_back(&grid[row_d][col_d]);
    }

    return neighbours;
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
            std::vector< Cell * > nbs = getNeighbours(row, col);
            grid[row][col].setNeighbours(nbs);
        }
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
            std::cout << tmp[row][col] + " ";
        }
        std::cout << "\n";  
    }

    for (auto &cell : grid[1][0].getNeighbours()) {
        std::cout << cell->package() + " ";
    }
    std::cout << "\n";
}