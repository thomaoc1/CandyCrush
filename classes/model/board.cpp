#include "board.hpp"

/***************************
 * PIVATE METHODS
 ***************************/

/**
 * @brief Insert random game component at indices row, col
 * 
 * @param row 
 * @param col 
 */
void Board::insertComponent(int row, int col) {
    int component = rand() % 10;

    // Wall insertion
    if (component == 7) board[row][col].setOccupied(std::make_shared<Wall>());

    // CandyBomb insertion
    else if (component == 8) board[row][col].setOccupied(std::make_shared<CandyBomb>());

    // Special Bomb insertion
    // else if (component == 9) {

    // Candy insertion
    else board[row][col].setOccupied(std::make_shared<Candy>());
}


/**
 * @brief Returns neighbours of game component at row, col
 * 
 * @param row 
 * @param col 
 * @return std::vector< std::shared_ptr<Cell> > 
 */
std::vector< std::shared_ptr<GameComponent> > Board::getNeighbours(int row, int col) const {
    std::vector< std::pair<int,int> > DELTA {{ 1, 0}, 
                                             { 0, 1}, 
                                             {-1, 0}, 
                                             { 0,-1}};
    
    std::vector< std::shared_ptr<GameComponent> > neighbours;
    
    for (auto &d : DELTA) {
        int row_d = row + d.first;
        int col_d = col + d.second;
        if (row_d >= static_cast<int>(board[0].size()) 
            || row_d < 0
            || col_d >= static_cast<int>(board.size())
            || col_d < 0 ) continue;
        
        neighbours.push_back(board[row_d][col_d].getOccupied());
    }

    return neighbours;
}


/***************************
 * PUBLIC METHODS
 ***************************/
Board::Board() {
    for (int row = 0; row < 9; ++row) {
        board.push_back(std::vector<Cell>(9));
        for (int col = 0; col < 9; ++col) {
            insertComponent(row, col);
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::vector< std::shared_ptr<GameComponent> > nbs = getNeighbours(row, col);
            board[row][col].setNeighbours(nbs);
        }
    }
}


/**
 * @brief Packages the board in to a vector of strings
 * 
 * @return std::vector< std::vector< std::string > > 
 */
std::vector< std::vector< std::string > > Board::package() const {
    std::vector< std::vector< std::string > > packagedBoard;
    for (int row = 0; row < 9; ++row) {
        packagedBoard.push_back({});
        for (int col = 0; col < 9; ++col) {
            packagedBoard[row].push_back(board[row][col].package());
        }
    }
    return packagedBoard;
}


/**
 * @brief Temporary method for displaying board
 * 
 */
void Board::display() const {
    std::vector< std::vector< std::string > > tmp = package();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::cout << tmp[row][col] + " ";
        }
        std::cout << "\n";  
    }

    for (auto &cell : board[4][4].getNeighbours()) {
        std::cout << cell->package() + " ";
    }
    std::cout << "\n";
}
