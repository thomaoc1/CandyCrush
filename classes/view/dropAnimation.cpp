#include "dropAnimation.hpp"

Point DropAnimation::currentTranslation(const Point &dest) {
    int x = static_cast<int>((time / animationTime) * (Constants::INTER_CELL * (cell->getLoc().x + dest.x) + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2));
    int y = static_cast<int>((time / animationTime) * (Constants::INTER_CELL * (cell->getLoc().y + dest.y) + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2));
    return {x, y};
}

void DropAnimation::draw(const Point &dest) {
    ++time;
    Translation t3{currentTranslation(dest)};
    cell->drawNoAnimation();
}