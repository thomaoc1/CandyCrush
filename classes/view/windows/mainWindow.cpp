#include "mainWindow.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                      Public Methods                                       *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


MainWindow::MainWindow() : Fl_Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "CandySmash") {
    Fl::add_timeout(1.0/Constants::FPS, Timer_CB, this);
    resizable(this);
}


/**
 * @brief Calls Fl_Window::draw() and displays the grid.
 * 
 */
void MainWindow::draw() {
    Fl_Window::draw();
    menuHandler.draw();   
}


/**
 * @brief Event handler.
 * 
 */
int MainWindow::handle(int event) {
    return menuHandler.eventHandler(event);
}


/**
 * @brief Call back method.
 * 
 * @param userdata
 * 
 */
void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow *)userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/Constants::FPS, Timer_CB, userdata);
}