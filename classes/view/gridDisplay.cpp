#include "gridDisplay.hpp"

void GridDisplay::draw() const {
    std::vector< std::vector < std::string > > packagedGrid = grid->package(); 
    const double upper_offset = (1.0 / 3.0) * dimensions.y; 
    const double middle_offset = (1.0 / 4.0) * dimensions.x;
    const double inter_offset = (1.0/ 4.0) * middle_offset;
    const double candySize = 30;
    // fl_draw_box(FL_FLAT_BOX, 0, 50, 1000, 1000, );
    for (int i = 0; i < static_cast<int>(packagedGrid.size()); ++i) {
        for (int j = 0; j < static_cast<int>(packagedGrid[i].size()); ++j) {
            std::string component = packagedGrid[i][j];
            if (component == Constants::RED);
            else if (component == Constants::BLUE) fl_color(FL_BLUE);
            else if (component == Constants::GREEN) fl_color(FL_GREEN);
            else if (component == Constants::YELLOW) fl_color(FL_YELLOW);
            else if (component == Constants::PURPLE) fl_color(FL_MAGENTA);
            else if (component == Constants::ORANGE) fl_color(FL_BLACK);
            else fl_color(FL_BLUE);
            fl_begin_polygon();
            fl_circle(inter_offset * i + middle_offset, inter_offset * j + upper_offset, candySize);
            fl_end_polygon();
        }
    }
    
}