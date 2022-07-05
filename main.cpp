#include "classes/model/grid.hpp"

int main() {

    Grid grid;
    grid.display();
    //std::cout << grid.checkSwap({0,2},{1,2}) << std::endl;
    //grid.display();
    //
    //grid.clean();
    //grid.display();
    std::cout << grid.checkSwap({6,1},{5,1}) << std::endl;
    grid.display();
    grid.clean();
    return 0;
}