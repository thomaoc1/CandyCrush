#include "mainWindow.hpp"

MainWindow::MainWindow() : Fl_Window(500, 500, "CandyCrush") {
    Fl::add_timeout(1.0/60, Timer_CB, this);
    resizable(this);
}

void MainWindow::draw() {
    Fl_Window::draw();
}

int MainWindow::handle(int event) {
    return event;
}

void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow *)userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/60, Timer_CB, userdata);
}