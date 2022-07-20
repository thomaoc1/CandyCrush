#include "gridControl.hpp"


/**
 * @brief
 * 
 * @param
 * 
 * @return
 * 
 */
Point GridControl::coordToCell(const Point &mouseLoc) const {
    int row = (mouseLoc.y - Constants::GAME_WINDOW_Yi) / Constants::INTER_CELL;
    int col = (mouseLoc.x - Constants::GAME_WINDOW_Xi) / Constants::INTER_CELL;
    return Point{col, row};
} 


/**
 * @brief
 * 
 * @param
 * 
 * @return
 * 
 */
bool GridControl::coordInGame(const Point &mouseLoc) const {
    return mouseLoc.x >= Constants::GAME_WINDOW_Xi
            && mouseLoc.x < Constants::GAME_WINDOW_Xf + Constants::INTER_CELL
            && mouseLoc.y >= Constants::GAME_WINDOW_Yi 
            && mouseLoc.y <= Constants::GAME_WINDOW_Yf + Constants::INTER_CELL;
}


/**
 * @brief
 * 
 * @param
 * 
 */
void GridControl::clickEvent(const Point &mouseLoc) {
    if (!coordInGame(mouseLoc)) return;
    clicked = true;
    click = mouseLoc;
    clickToIndex = coordToCell(mouseLoc);
    std::cout << "Click: " << grid->getCell(clickToIndex.y, clickToIndex.x) << std::endl;
}


/**
 * @brief
 * 
 * @param
 * 
 */
void GridControl::dragEvent(const Point &mouseLoc) {
    if (!(clicked && coordInGame(mouseLoc))) return;
    Point dragToIndex = coordToCell(mouseLoc);
    std::cout << "DRAG Row : " << dragToIndex.y << " Col : " << dragToIndex.x << std::endl;
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
 * @brief
 * 
 * @param
 * 
 * @return
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

