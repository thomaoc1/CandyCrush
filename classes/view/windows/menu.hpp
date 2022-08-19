/**
 * @file menu.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Abstract class which generalises the graphical representation and
 *  behaviour of a Menu.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef MENU_HPP
#define MENU_HPP

#include "../common/background.hpp"

class Menu {
protected:
    Background bg{FL_WHITE};
    bool back = false;
public:
    Menu() = default;
    virtual ~Menu() = default;
    virtual void draw() {bg.draw();}
    virtual int eventHandler(int event)=0;
};


#endif