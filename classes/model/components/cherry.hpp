#ifndef CHERRY_HPP
#define CHERRY_HPP

#include "gameComponent.hpp"

class Cherry : public GameComponent {
public:
    Cherry() = default;
    Cherry(const Cherry &) = default;
    Cherry(Cherry &&) = default;
    
    int type() const override {return Constants::CHERRY;}
    //std::string toString() const override {return "C";}  
};

#endif