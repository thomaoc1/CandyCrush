#include "point.hpp"

std::ostream & operator << (std::ostream &out, const Point &p) {
    out << "{" << p.y << ", " << p.x << "}";
    return out;
}