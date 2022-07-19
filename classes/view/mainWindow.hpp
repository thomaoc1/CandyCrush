#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../constants/constants.hpp"
#include "../model/grid.hpp"
#include "../control/gridControl.hpp"
#include "../control/gridObserver.hpp"
#include "gridDisplay.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <vector>
#include <string>

class MainWindow : public Fl_Window {
    std::shared_ptr<Grid> grid;
    GridControl gridControl;
    GridObserver gridObserver;
    GridDisplay gridDisplay;
public:
    MainWindow();
    //GridDisplay * getGridDisplay() {return &gridDisplay;}
    void draw() override;
    int handle(int event) override;
    static void Timer_CB(void *userdata);
};

#endif