/**
 * @file hazelnut.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a Hazelnut component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef HAZELNUT_HPP
#define HAZELNUT_HPP

#include "gameComponent.hpp"

class Hazelnut : public GameComponent {
public:
    Hazelnut() : GameComponent{ComponentType{Colour::BROWN, Component::HAZELNUT}} {}
    Hazelnut(const Hazelnut &) = default;
    Hazelnut(Hazelnut &&) = default;
};

#endif