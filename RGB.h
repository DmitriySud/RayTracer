//
// Created by dimasya on 09.01.2021.
//
#ifndef SHAD_CPP0_RGB_H
#define SHAD_CPP0_RGB_H


#include <fstream>
#include "Vector3D.h"
struct RGB {
    explicit RGB(const Vector3D& vector)
        : r(vector.x * 255) , g(vector.y* 255), b(vector.z * 255) {
    }

    RGB (int r, int g, int b)
        : r(r), g(g), b(b){

    }

    RGB() :r(0), g(0), b(0){

    }

    bool operator==(const RGB& rhs) const {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    RGB operator+(const RGB& other) const{
        return RGB(r + other.r, g + other.g, b + other.b);
    }

    RGB& operator+=(const RGB& other) {
        r += other.r;
        g += other.g;
        b += other.b;

        return *this;
    }

    int r, g, b;

};

std::istream& operator>> (std::istream& in, RGB& rgb){
    double rd, gd, bd;
    in >> rd >> gd >> bd;
    rgb.r = rd * 255;
    rgb.g = gd * 255;
    rgb.b = bd * 255;

    return in;
}


#endif  // SHAD_CPP0_RGB_H
