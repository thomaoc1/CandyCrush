/**
 * @file point.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Struct used to store coordinates
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point{
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x{x}, y{y} {}

    Point operator+(const Point &other) const {return {x + other.x, y + other.y};}
    Point operator-(const Point &other) const {return {x - other.x, y - other.y};}
    void operator+=(const Point &other) {x += other.x; y += other.y;}
    bool operator==(const Point &other) {return x == other.x && y == other.y;}
    friend std::ostream & operator<<(std::ostream &out, const Point &p);
};

#endif