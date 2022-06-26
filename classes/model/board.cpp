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
    if (component == 7) board[row][col] = std::make_shared<Wall>();

    // CandyBomb insertion
    else if (component == 8) board[row][col] = std::make_shared<CandyBomb>();

    // Special Bomb insertion
    // else if (component == 9) {

    // Candy insertion
    else board[row][col] = std::make_shared<Candy>();
}


/***************************
 * PUBLIC METHODS
 ***************************/
Board::Board() {
    for (int row = 0; row < 9; ++row) {
        board.push_back(std::vector< std::shared_ptr<Cell> >(9));
        for (int col = 0; col < 9; ++col) {
            insertComponent(row, col);
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
            packagedBoard[row].push_back(board[row][col]->package());
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
}
