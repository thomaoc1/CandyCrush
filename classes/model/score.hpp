#ifndef SCORE_HPP
#define SCORE_HPP

#include "../constants/constants.hpp"
#include "../view/gridDisplay.hpp"

#include <iostream>
#include <memory>

class Score {
    int score = 0;
    int bSpawn = 35;
    int explMuti = 20;
    int suppression = 15;

    GridDisplay &observer;
public:
    Score(GridDisplay &observer) : observer{observer} {}
    Score(const Score &) = default;
    Score(Score &&) = default;
    
    void bombSpawn(int count, int component);
    void pop(int count);
};

#endif