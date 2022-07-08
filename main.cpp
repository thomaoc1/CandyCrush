#include "classes/view/mainWindow.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char *argv[]) {
  //srand(time(0));
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}
