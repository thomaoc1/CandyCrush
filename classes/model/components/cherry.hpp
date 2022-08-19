/**
 * @file cherry.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a Cherry component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef CHERRY_HPP
#define CHERRY_HPP

#include "gameComponent.hpp"

class Cherry : public GameComponent {
public:
    Cherry() : GameComponent{ComponentType{Colour::DARK_RED, Component::CHERRY}} {}
    Cherry(const Cherry &) = default;
    Cherry(Cherry &&) = default;
};

#endif