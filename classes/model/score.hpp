/**
 * @file gameObjective.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of updating the player's score.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef SCORE_HPP
#define SCORE_HPP

#include "../common/constants.hpp"
#include "../view/gridDisplay.hpp"

#include <iostream>
#include <memory>

class Score {
    int score = 0;
    const int bSpawn = 35;
    const int explMuti = 20;
    const int suppression = 15;

    GridDisplay &observer;
public:
    Score(GridDisplay &observer) : observer{observer} {}
    Score(const Score &) = default;
    Score(Score &&) = default;
    
    int getScore() const {return score;}
    void reset();
    void bombSpawn(int count, Component component);
    void pop(int count);
};

#endif