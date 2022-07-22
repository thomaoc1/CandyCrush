#include "mainWindow.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                      Public Methods                                       *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


MainWindow::MainWindow() : Fl_Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "CandySmash"),
                            gridDisplay{std::make_shared<GridDisplay>()},
                            grid{std::make_shared<Grid>(gridDisplay)}, 
                            gridControl{grid} {
    Fl::add_timeout(1.0/Constants::FPS, Timer_CB, this);
    resizable(this);
}


/**
 * @brief Calls Fl_Window::draw() and displays the grid.
 * 
 */
void MainWindow::draw() {
    Fl_Window::draw();
    gridDisplay->draw();
}


/**
 * @brief Event handler.
 * 
 */
int MainWindow::handle(int event) {
    return gridControl.proccessEvent(event);
}


/**
 * @brief Call back method. Called Constants::FPS times per second.
 * 
 * @param userdata
 * 
 */
void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow *)userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/Constants::FPS, Timer_CB, userdata);
}