/**
 * @file componentType.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Data struture which represents a game component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef COMPONENT_TYPE_HPP
#define COMPONENT_TYPE_HPP

#include "enumerations.hpp"

struct ComponentType {
    Colour colour;
    Component type;

    ComponentType(Colour colour, Component type)
        : colour{colour}, type{type} {}
    ComponentType() : colour{Colour::BLACK}, type{Component::ANY} {}
};

#endif