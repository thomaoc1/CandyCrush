#include "score.hpp"

void Score::bombSpawn(int count, int component) {
    switch (component) {
        case Constants::WRAPPED:
            score += count * 35;
            break;
        case Constants::STRIPED:
            score += count * 25;
            break;
        case Constants::SPECIAL:
            score += count * 50;
            break;
    }
    observer->notifyScore(score);
}


void Score::pop(int count) {
    score += (suppression * count) + pow(explMuti, count);
    observer->notifyScore(score);
}