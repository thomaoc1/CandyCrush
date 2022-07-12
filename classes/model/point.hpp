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
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x{x}, y{y} {}

    Point operator+(const Point &other) const {return {x + other.x, y + other.y};}
    Point operator-(const Point &other) const {return {x - other.x, y - other.y};}
    void operator+=(const Point &other) {x += other.x; y += other.y;}
};

#endif