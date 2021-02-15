//
// Created by dimasya on 09.01.2021.
//

#ifndef SHAD_CPP0_LIGHTSOURCE_H
#define SHAD_CPP0_LIGHTSOURCE_H

#include "RGB.h"
#include "Vector3D.h"

struct LightSource{
    LightSource(const Vector3D& point, const Vector3D& rgb) : point(point), rgb(rgb) {
    }
    Vector3D point;
    Vector3D rgb;
};

#endif  // SHAD_CPP0_LIGHTSOURCE_H
