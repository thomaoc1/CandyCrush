#include "gridControl.hpp"


/**
 * @brief Converts mouse location to matrix indices
 * 
 * @param mouseLoc
 * 
 * @return Point
 * 
 */
Point GridControl::coordToCell(const Point &mouseLoc) const {

    int row = -1;
    int col = -1;

    int x_dividend = mouseLoc.x -  Constants::GAME_WINDOW_Xi;
    int x_divisor = Constants::CELL_SIZE + Constants::GAP_SIZE;

    float x_quotient = x_dividend / x_divisor;
    float x_remainder = x_dividend % x_divisor;

    int y_dividend = mouseLoc.y -  Constants::GAME_WINDOW_Yi;
    int y_divisor = Constants::CELL_SIZE + Constants::GAP_SIZE;

    float y_quotient = y_dividend / y_divisor;
    float y_remainder = y_dividend % y_divisor;

    if (x_remainder <= Constants::CELL_SIZE && y_remainder <= Constants::CELL_SIZE ) {
        col = x_quotient;
        row = y_quotient;
    }
    return Point{col, row};
} 


/**
 * @brief Checks if the coordinate given is in the game's allocated rectangle
 * 
 * @param mouseLoc
 * 
 * @return Point
 * 
 */
bool GridControl::coordInGame(const Point &mouseLoc) const {
    return mouseLoc.x > Constants::GAME_WINDOW_Xi
            && mouseLoc.x < Constants::GAME_WINDOW_Xf 
            && mouseLoc.y > Constants::GAME_WINDOW_Yi 
            && mouseLoc.y < Constants::GAME_WINDOW_Yf ;
}


/**
 * @brief If the click is in the game window, the location is converted matrix indices.
 * 
 * @param mouseLoc
 * 
 */
void GridControl::clickEvent(const Point &mouseLoc) {
    if (!coordInGame(mouseLoc) 
        || (coordInGame(mouseLoc) && inAnimation())
        || (coordInGame(mouseLoc) && gameOver())) return;

    dragged = false;
    click = mouseLoc;
    clickToIndex = coordToCell(mouseLoc);
}


/**
 * @brief Verifies drag conditions and converts the drag location to matrix indices.
 * 
 * @param mouseLoc
 * 
 */
void GridControl::dragEvent(const Point &mouseLoc) {
    if (dragged || !coordInGame(mouseLoc) 
                || (coordInGame(mouseLoc) && view.inAnimation())
                || coordToCell(mouseLoc) == clickToIndex) return;
                
    Point dragToIndex = coordToCell(mouseLoc);
    
    // -1 means the mouse is over a gap
    if ( dragToIndex.x == -1 || dragToIndex.y == -1 ) return;
    
    dragged = true;

    if (dragToIndex.x == clickToIndex.x) {
        if (dragToIndex.y < clickToIndex.y) {
            grid->swap(clickToIndex, {clickToIndex.x, clickToIndex.y - 1});
        }
        else if (dragToIndex.y > clickToIndex.y) {
            grid->swap(clickToIndex, {clickToIndex.x, clickToIndex.y + 1});
        }
    }
    else if (dragToIndex.y == clickToIndex.y) {
        if (dragToIndex.x < clickToIndex.x) {
            grid->swap(clickToIndex, {clickToIndex.x - 1, clickToIndex.y});
        }
        else if (dragToIndex.x > clickToIndex.x) {
            grid->swap(clickToIndex, {clickToIndex.x + 1, clickToIndex.y});
        }
    }
}


/**
 * @brief Event processor
 * 
 * @param event
 * 
 * @return bool
 * 
 */
int GridControl::proccessEvent(int event) {
    switch (event) {
        case FL_PUSH : {
            if (Fl::event_button() != FL_LEFT_MOUSE) break;
            
            clickEvent({Fl::event_x(), Fl::event_y()});
            break;
        }
        case FL_RELEASE : {
            if (Fl::event_button() != FL_LEFT_MOUSE) break;
            dragged = false;
            click = Point{};
            break;
        }
        case FL_DRAG:
            if (Fl::event_button() != FL_LEFT_MOUSE) break;

            dragEvent({Fl::event_x(), Fl::event_y()});
            break;

        case FL_KEYDOWN:
            Log::get().Dump();
            exit(0);
    } 

    int state = (grid->gameState() == LOST || grid->gameState() == WON) ? Constants::GAME_OVER : Constants::GAME_ONGOING;
    return state;
}

