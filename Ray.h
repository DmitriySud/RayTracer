//
// Created by dimasya on 17.01.2021.
//

#ifndef SHAD_CPP0_RAY_H
#define SHAD_CPP0_RAY_H

#include "Vector3D.h"

struct Ray{
    Ray(const Vector3D& point, const Vector3D& direction)
        : point(point), direction(direction.Normalize()){

    }


    Vector3D point;
    Vector3D direction;
};

#endif  // SHAD_CPP0_RAY_H
