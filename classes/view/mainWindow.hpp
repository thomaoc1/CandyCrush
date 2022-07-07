#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../constants/constants.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <vector>
#include <string>

class MainWindow : public Fl_Window {
    std::vector< std::vector< std::string > > grid;
public:
    MainWindow();
    void draw() override;
    int handle(int event) override;
    static void Timer_CB(void *userdata);
};

#endif