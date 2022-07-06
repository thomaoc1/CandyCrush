#include "gameControl.hpp"

void GameControl::gameLoop() {
    while (true) {
        typedef std::pair< Point, Point > PointPair;
        view.displayGrid();
        PointPair input = view.displayTurn();
        while (!grid.checkSwap(input.first, input.second)) view.displayTurn();
        view.displayGrid();
        break;
    }
}