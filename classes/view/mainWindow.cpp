#include "mainWindow.hpp"

MainWindow::MainWindow() : Fl_Window(1000, 1000, "CandySmash"), grid{std::make_shared<Grid>()}, 
                                        gridControl{grid}, gridDisplay{grid, Point{1000, 1000}} {
    Fl::add_timeout(1.0/60, Timer_CB, this);
    resizable(this);
}

void MainWindow::draw() {
    Fl_Window::draw();
    gridDisplay.draw();
}

int MainWindow::handle(int event) {
    return gridControl.proccessEvent(event);
}

void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow *)userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/60, Timer_CB, userdata);
}