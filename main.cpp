#include "classes/model/grid.hpp"

int main() {

    Grid grid;
    grid.display();
    //std::cout << grid.checkSwap({0,2},{1,2}) << std::endl;
    //grid.display();
    //
    grid.clean();
    grid.display();

    return 0;
}