/**
 * File : 
 *  mainWindow.hpp
 *
 * Decription :
 *  Class responsible of creating the FL_Window.
 * 
 * Dependencies:
 *  constants.hpp
 *  grid.hpp
 *  gridControl.hpp
 *  gridDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../constants/constants.hpp"
#include "../model/containers/grid.hpp"
#include "../control/gridControl.hpp"
#include "gridDisplay.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainWindow : public Fl_Window {
    std::shared_ptr<GridDisplay> gridDisplay;
    std::shared_ptr<Grid> grid;
    GridControl gridControl;
public:
    MainWindow();
    void draw() override;
    int handle(int event) override;
    static void Timer_CB(void *userdata);
};

#endif