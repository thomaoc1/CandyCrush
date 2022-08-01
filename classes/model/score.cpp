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
    // std::cout << score << std::endl;
}


void Score::pop(int count) {
    score += (suppression * count) + (explMuti * count);
    // std::cout << score << std::endl;
}