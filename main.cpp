#include "classes/control/gridControl.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main() {

    
    std::shared_ptr<Grid> grid = std::make_shared<Grid>();
    GridControl gc{grid};

    return Fl::run();
}