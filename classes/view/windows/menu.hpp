#ifndef MENU_HPP
#define MENU_HPP

class Menu {
protected:
    bool back = false;
public:
    Menu()=default;
    virtual bool getBack() {return back;}
    virtual void draw()=0;
    virtual int eventHandler(int event)=0;
};


#endif