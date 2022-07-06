#include "GUI.hpp"

GUI::PointPair GUI::displayTurn() const {
    int x, y, x1, y1;
    std::string input;
    std::cout << "Swap two candies format(x y x1 y1)";
    std::cin >> input;
    std::cout << std::endl;

    x = (int)input.at(0) - (int)'0';
    y = (int)input.at(1) - (int)'0';
    x1 = (int)input.at(2) - (int)'0';
    y1 = (int)input.at(3) - (int)'0';

    std::cout << x << " " << y << "\n" << x1 << " " << y << std::endl;

    return {{x, y}, {x1, y1}};
}

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