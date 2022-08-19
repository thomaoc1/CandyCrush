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