#ifndef SCORE_DISPLAY_HPP 
#define SCORE_DISPLAY_HPP

#include "text.hpp"

class ScoreDisplay : public Text {
public:
    ScoreDisplay(const Point &center, int size, int score=0)
        : Text{center, "Score: " + std::to_string(score), FL_HELVETICA, size} {}
    ScoreDisplay() = default;
    ScoreDisplay(const ScoreDisplay &) = default;
    ScoreDisplay(ScoreDisplay &&) = default;

    void setText(const std::string &message) override {text = "Score: " + message;}
    void setText(std::string &&message) override {text = "Score: " + message;}
    void draw() const override;
};

#endif