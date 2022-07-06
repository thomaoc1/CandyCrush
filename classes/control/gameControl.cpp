#include "gameControl.hpp"

void GameControl::fill() {
    while (grid.fill()) {
        std::cout << "=== Fill ===" << std::endl;
        view.displayGrid();
        drop();
        view.displayGrid();
    }
} 

void GameControl::drop() {
    bool dropComplete = false;
    while (!dropComplete)  {
        std::cout << "=== Drop Down ===" << std::endl;
        // Drop down until can't
        while(grid.directedDrop(Constants::BELOW));
        view.displayGrid();
        std::cout << "=== Drop Left ===" << std::endl;
        // DirectedDrop(Left) -> true : means at least one candy was dropped. !!! So restart DropDown 
        // DirectedDrop(Left) -> false : means no candy was dropped to the left, therefore start DropRight 
        if (!grid.directedDrop(Constants::BELOW_LEFT)) {
            std::cout << "=== Drop Right ===" << std::endl;
            // DirectedDrop(Right) -> true : means at least candy was dropped. !!! So restart DropDown 
            // DirectedDrop(Right) -> false : means no candy was dropped to the Right, therefore Complete Drop 
            if (!grid.directedDrop(Constants::BELOW_RIGHT)) dropComplete = true;
        }
        view.displayGrid();
    }
}


void GameControl::clean() {
    while (!grid.clear()) {
        std::cout << "=== Clear ===" << std::endl;
        view.displayGrid();
        drop();
        fill();
    } 
}

void GameControl::gameLoop() {
    typedef std::pair< Point, Point > PointPair;
    while (true) {
        view.displayGrid();
        clean();
        PointPair input = view.displayTurn();
        while (!grid.checkSwap(input.first, input.second)) view.displayTurn();
    }
}