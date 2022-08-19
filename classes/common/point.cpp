#include "point.hpp"


std::ostream & operator << (std::ostream &out, const Point &p) {
    out << "{x, y} : " << "{" << p.x << ", " << p.y << "}";
    return out;
}