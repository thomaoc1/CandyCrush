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
    ~CandyBomb() {}
    const std::string package() const override {return Constants::BOMB + Candy::package();}
}; 

#endif