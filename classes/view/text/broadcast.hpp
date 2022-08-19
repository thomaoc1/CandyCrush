#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#include "broadcastText.hpp"
#include "scoreDisplay.hpp"
#include "swapsLeftDisplay.hpp"
#include "objectiveDisplay.hpp"
#include "../shapes/rectangle.hpp"

class BroadcastBox {
    Rectangle box;
    BroadcastText text;
    ScoreDisplay score;
    SwapsLeftDisplay swaps;
    ObjectiveDisplay objective;

public:
    BroadcastBox(const std::string &s = "")
     : box{Point{static_cast<int>(Constants::WINDOW_WIDTH / 2), 125}, 
            FL_BLACK, Constants::GAME_WINDOW_Xf - Constants::GAME_WINDOW_Xi, 150, FL_BORDER_FRAME}, 
        text{box.getCenter(), 30, s}, score{box.getCenter(), 15}, swaps{box.getCenter(), 15}, objective{box.getCenter(), 15} {}

    void clear() {text.clear();}
    void setMessage(const std::string &s) {text.setText(s);}
    void setMessage(std::string &&s) {text.setText(std::move(s));}
    void setSwaps(int nbSwaps) {swaps.setText(std::to_string(nbSwaps));}
    void setScore(int newScore) {score.setText(std::to_string(newScore));}
    void setObjective(ObjectiveType objType, int obj);
    void setObjective(ObjectiveType objType, int obj, Colour colour);

    void clearHelpMessage() {if (getText() == Constants::BAD_SWAP) clear();}
    void draw() const;

private:
    std::string getText() const {return text.getText();}
};


#endif