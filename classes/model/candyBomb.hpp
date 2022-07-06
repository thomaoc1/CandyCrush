/**
 * File : 
 *  candyBomb.hpp
 *
 * Decription :
 *  Class which represents a specific GameComponent ; "CandyBomb"
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef CANDYBOMB_HPP
#define CANDYBOMB_HPP

#include "candy.hpp"

class CandyBomb : public Candy {
public:
    CandyBomb() : Candy() {}
    CandyBomb(const std::string &colour) : Candy(colour) {}
    ~CandyBomb() {}
    virtual const std::string package() const override {return Candy::package() + Constants::BOMB;}
}; 

#endif