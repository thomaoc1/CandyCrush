/**
 * File : 
 *  Point.hpp
 *
 * Decription :
 *  Struct to store to ints, typically for matrix coordinates
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef POINT_HPP
#define POINT_HPP

struct Point{
    Point(int x, int y) : x{x}, y{y} {}
    int x;
    int y;
};

#endif