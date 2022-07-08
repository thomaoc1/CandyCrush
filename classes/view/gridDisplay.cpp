#include "gridDisplay.hpp"

void GridDisplay::draw() const {
    std::vector< std::vector < int > > packagedGrid = grid->package(); 
    const double upper_offset = (1.0 / 3.0) * dimensions.y; 
    const double middle_offset = (1.0 / 4.0) * dimensions.x;
    const double inter_offset = (1.0/ 4.0) * middle_offset;
    const double candySize = 30;
    // fl_draw_box(FL_FLAT_BOX, 0, 50, 1000, 1000, );
    for (int i = 0; i < static_cast<int>(packagedGrid.size()); ++i) {
        for (int j = 0; j < static_cast<int>(packagedGrid[0].size()); ++j) {
            switch (packagedGrid[i][j]) {
                case Constants::RED:
                    fl_color(FL_DARK_RED);
                    break;        
                case Constants::BLUE:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN:
                    fl_color(FL_GREEN);
                    break;
                case Constants::PURPLE:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::YELLOW:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::ORANGE:
                    fl_color(FL_RED);
                    break;
                case Constants::RED_STRIPED_BOMB:
                    fl_color(FL_DARK_RED);
                    break;
                case Constants::BLUE_STRIPED_BOMB:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN_STRIPED_BOMB:
                    fl_color(FL_GREEN);
                    break;
                case Constants::YELLOW_STRIPED_BOMB:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::PURPLE_STRIPED_BOMB:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::ORANGE_STRIPED_BOMB:
                    fl_color(FL_RED);
                    break;        
                case Constants::RED_WRAPPED_BOMB:
                    fl_color(FL_DARK_RED);
                    break;
                case Constants::BLUE_WRAPPED_BOMB:
                    fl_color(FL_BLUE);
                    break;
                case Constants::GREEN_WRAPPED_BOMB:
                    fl_color(FL_GREEN);
                    break;
                case Constants::YELLOW_WRAPPED_BOMB:
                    fl_color(FL_YELLOW);
                    break;
                case Constants::PURPLE_WRAPPED_BOMB:
                    fl_color(FL_MAGENTA);
                    break;
                case Constants::ORANGE_WRAPPED_BOMB:
                    fl_color(FL_RED);
                    break;
                case Constants::WALL:
                    fl_color(FL_BLACK);
                    break;
            }
            fl_begin_polygon();
            fl_circle(inter_offset * j + middle_offset, inter_offset * i + upper_offset, candySize);
            fl_end_polygon();
        }
    }
}