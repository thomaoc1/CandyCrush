#ifndef MENU_HPP
#define MENU_HPP

class Menu {
protected:
    Background bg{FL_WHITE};
    bool back = false;
public:
    Menu()=default;
    virtual bool getBack() {return back;}
    virtual void draw() {bg.draw();}
    virtual int eventHandler(int event)=0;
};


#endif