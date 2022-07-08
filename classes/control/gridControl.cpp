#include "gridControl.hpp"


Point GridControl::coordToCell(const Point &mouseLoc) const {
    //int row = ((mouseLoc.y - Constants::GAME_WINDOW_Yi)  / (Constants::GAME_WINDOW_Yi - Constants::CELL_SIZE));
    int row = (mouseLoc.y - Constants::GAME_WINDOW_Yi + Constants::CELL_SIZE) / Constants::INTER_CELL;
    int col = (mouseLoc.x - Constants::GAME_WINDOW_Xi + Constants::CELL_SIZE) / Constants::INTER_CELL;
    return Point{col, row};
} 


bool GridControl::clickInGame(const Point &mouseLoc) const {
    return mouseLoc.x >= Constants::GAME_WINDOW_Xi - Constants::CELL_SIZE 
            && mouseLoc.x < Constants::GAME_WINDOW_Xf + Constants::CELL_SIZE
            && mouseLoc.y >= Constants::GAME_WINDOW_Yi - Constants::CELL_SIZE
            && mouseLoc.y <= Constants::GAME_WINDOW_Yf + Constants::CELL_SIZE;
}


bool GridControl::clickEvent(const Point &mouseLoc) {
    clicked = false;
    // std::cout << "Click: " << mouseLoc.x << " " << mouseLoc.y << std::endl;
    if (clickInGame(mouseLoc)) {
        clicked = true;
        click = mouseLoc;
        clickToIndex = coordToCell(mouseLoc);
        //std::cout << "[" << clickToIndex.y << "," << clickToIndex.x << "]" << std::endl;
        //std::cout << "Colour : " << grid->getCell(clickToIndex.y, clickToIndex.x)<< std::endl;
    }
    return clicked;
}


void GridControl::dragEvent(const Point &mouseLoc) {
    if (!clicked) return;
    bool swapped = false;
    Point dragToIndex = coordToCell(mouseLoc);
    std::cout << "DRAG Row : " << dragToIndex.y << " Col : " << dragToIndex.x << std::endl;
    if (dragToIndex.x == clickToIndex.x) {
        if (dragToIndex.y < clickToIndex.y) {
            swapped = grid->checkSwap(clickToIndex, {clickToIndex.x, clickToIndex.y - 1});
        }
        else if (dragToIndex.y > clickToIndex.y) {
            swapped = grid->checkSwap(clickToIndex, {clickToIndex.x, clickToIndex.y + 1});
        }
    }
    else if (dragToIndex.y == clickToIndex.y) {
        if (dragToIndex.x < clickToIndex.x) {
            swapped = grid->checkSwap(clickToIndex, {clickToIndex.x - 1, clickToIndex.y});
        }
        else if (dragToIndex.x > clickToIndex.x) {
            swapped = grid->checkSwap(clickToIndex, {clickToIndex.x + 1, clickToIndex.y});
        }
    }
    if (swapped) clean();
}


bool GridControl::proccessEvent(int event) {
    switch (event) {
        case FL_PUSH : {
            if (Fl::event_button() != FL_LEFT_MOUSE) break;
            
            clickEvent({Fl::event_x(), Fl::event_y()});
            break;
        }
        case FL_RELEASE : {
            if (Fl::event_button() != FL_LEFT_MOUSE) break;
            clicked = false;
            click = Point{};
            break;
        }
        case FL_DRAG:
            if (Fl::event_button() != FL_LEFT_MOUSE) break;

            dragEvent({Fl::event_x(), Fl::event_y()});
            break;
    } 
    return event;
}


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
}