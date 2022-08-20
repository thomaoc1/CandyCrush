/**
 * @file componentText.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of the 
 * Component text.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef COMPONENT_TEXT_HPP
#define COMPONENT_TEXT_HPP

#include "text.hpp"

class ComponentText : public Text {
public:
    ComponentText(const Point &center, const std::string &text, Fl_Font font, int size)
        : Text{center, text, font, size} {}
    ComponentText() = default;
    ComponentText(const ComponentText &) = default;
    ComponentText(ComponentText &&) = default;
    void draw() const override;
};

#endif