#include "cell.hpp"

std::string Cell::package() const {
    return occupied ? occupied->package() : Constants::getEMPTY();
}