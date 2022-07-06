#include "GUI.hpp"

void GUI::displayGrid() const {
    std::vector< std::vector< std::string > > tmp = grid.package();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (tmp[row][col].length() == 1) std::cout << tmp[row][col] + "   ";
            else std::cout << tmp[row][col] + " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n"; 
}