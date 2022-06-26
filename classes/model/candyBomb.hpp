#ifndef CANDYBOMB_HPP
#define CANDYBOMB_HPP

#include "candy.hpp"

class CandyBomb : public Candy {
public:
    CandyBomb() : Candy() {}
    ~CandyBomb() {}
    std::string package() const override {return Constants::getBOMB() + Candy::package();}
}; 

#endif