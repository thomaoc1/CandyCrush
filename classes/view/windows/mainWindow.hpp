/**
 * @file mainWindow.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for launching an FLTK Window and forwarding
 *  events.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../../common/constants.hpp"
#include "../../model/containers/grid.hpp"
#include "../../control/gridControl.hpp"
#include "../gridDisplay.hpp"
#include "titleScreen.hpp"
#include "menuHandler.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainWindow : public Fl_Window {
    MenuHandler menuHandler;
    TitleScreen ts;
    int time = 90;
public:
    MainWindow();
    void draw() override;
    int handle(int event) override;
    static void Timer_CB(void *userdata);
};

#endif