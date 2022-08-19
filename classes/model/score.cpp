#include "score.hpp"


void Score::reset() {
    score = 0;
    observer.notifyScore(score);
}


void Score::bombSpawn(int count, Component component) {
    switch (component) {
        case Component::WRAPPED_BOMB:
            score += count * 35;
            break;
        case Component::STRIPED_BOMB_H:
        case Component::STRIPED_BOMB_V:
            score += count * 25;
            break;
        case Component::SPECIAL_BOMB:
            score += count * 50;
            break;
        default:
            break;
    }
    observer.notifyScore(score);
}


void Score::pop(int count) {
    score += (suppression * count) + (explMuti * count);
    observer.notifyScore(score);
}