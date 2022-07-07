#include "gridControl.hpp"

void GridControl::fill() {
    while (grid->fill()) {
        std::cout << "=== Fill ===" << std::endl;
        // view.displayGrid();
        drop();
        // view.displayGrid();
    }
} 

void GridControl::drop() {
    bool dropComplete = false;
    while (!dropComplete)  {
        std::cout << "=== Drop Down ===" << std::endl;
        // Drop down until can't
        while(grid->directedDrop(Constants::BELOW));
        // view->displayGrid();
        std::cout << "=== Drop Left ===" << std::endl;
        // DirectedDrop(Left) -> true : means at least one candy was dropped. !!! So restart DropDown 
        // DirectedDrop(Left) -> false : means no candy was dropped to the left, therefore start DropRight 
        if (!grid->directedDrop(Constants::BELOW_LEFT)) {
            std::cout << "=== Drop Right ===" << std::endl;
            // DirectedDrop(Right) -> true : means at least candy was dropped. !!! So restart DropDown 
            // DirectedDrop(Right) -> false : means no candy was dropped to the Right, therefore Complete Drop 
            if (!grid->directedDrop(Constants::BELOW_RIGHT)) dropComplete = true;
        }
        // view.displayGrid();
    }
}


void GridControl::clean() {
    while (!grid->clear()) {
        std::cout << "=== Clear ===" << std::endl;
        drop();
        fill();
    } 
}

void GridControl::gameLoop() {
    typedef std::pair< Point, Point > PointPair;
}