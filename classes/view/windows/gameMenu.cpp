#include "gameMenu.hpp"

std::string GameMenu::associatedFile(MenuButtons level) const {
    std::string filename = "";
    switch(level) {
        case MenuButtons::LEVEL1:
            filename = "db/levels/level1.txt";
            break;
        case MenuButtons::LEVEL2:
            filename = "db/levels/level2.txt";
            break;
        case MenuButtons::LEVEL3:
            filename = "db/levels/level3.txt";
            break;
        default:
            break;
    }
    return filename;
}
