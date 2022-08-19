/**
 * @file specialBomb.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a SpecialBomb component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef SPECIAL_BOMB_HPP
#define SPECIAL_BOMB_HPP

#include "gameComponent.hpp"

class SpecialBomb : public GameComponent {
public:
    SpecialBomb() 
        : GameComponent{ComponentType{Colour::DARK_RED, Component::SPECIAL_BOMB}} {}
};

#endif