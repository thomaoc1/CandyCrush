#include "gameMenu.hpp"

std::string GameMenu::associatedFile(int level) const {
    std::string filename = "";
    switch(level) {
        case Constants::LEVEL1:
            filename = "db/levels/level1.txt";
            break;
        case Constants::LEVEL2:
            filename = "db/levels/level2.txt";
            break;
        case Constants::LEVEL3:
            filename = "db/levels/level3.txt";
            break;
    }

    return filename;
}
