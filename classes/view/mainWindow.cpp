#include "mainWindow.hpp"

MainWindow::MainWindow() : Fl_Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "CandySmash"), grid{std::make_shared<Grid>()}, 
                                        gridControl{grid}, gridDisplay{grid} {
    gridObserver.setObserver(&gridDisplay);
    Fl::add_timeout(1.0/Constants::FPS, Timer_CB, this);
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
    Fl::repeat_timeout(1.0/Constants::FPS, Timer_CB, userdata);
}