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
    int row = (mouseLoc.y - Constants::GAME_WINDOW_Yi) / Constants::INTER_CELL;
    int col = (mouseLoc.x - Constants::GAME_WINDOW_Xi) / Constants::INTER_CELL;
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
    return mouseLoc.x >= Constants::GAME_WINDOW_Xi
            && mouseLoc.x < Constants::GAME_WINDOW_Xf + Constants::INTER_CELL
            && mouseLoc.y >= Constants::GAME_WINDOW_Yi 
            && mouseLoc.y <= Constants::GAME_WINDOW_Yf + Constants::INTER_CELL;
}


/**
 * @brief If the click is in the game window, the location is converted matrix indices.
 * 
 * @param mouseLoc
 * 
 */
void GridControl::clickEvent(const Point &mouseLoc) {
    if (!coordInGame(mouseLoc) || (coordInGame(mouseLoc) && view->inAnimation())) return;
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
                || (coordInGame(mouseLoc) && view->inAnimation())
                || coordToCell(mouseLoc) == clickToIndex) return;
                
    Point dragToIndex = coordToCell(mouseLoc);
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
bool GridControl::proccessEvent(int event) {
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
    return event;
}

