#include "classes/view/windows/mainWindow.hpp"


int main(int argc, char *argv[]) {

  Log::get().addViewMessage("Start View Log\n\n");
  Log::get().addModelMessage("Start Model Log\n\n");

  //srand(time(0));
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}
