#ifndef SCORE_HPP
#define SCORE_HPP

#include "../constants/constants.hpp"
#include "../view/gridDisplay.hpp"

#include <iostream>
#include <memory>
#include <math.h>

class Score {
    int score = 0;
    int bSpawn = 35;
    int explMuti = 2;
    int suppression = 15;

    std::shared_ptr<GridDisplay> observer;
public:
    Score(std::shared_ptr<GridDisplay> observer) : observer{observer} {}
    void bombSpawn(int count, int component);
    void pop(int count);
};

#endif