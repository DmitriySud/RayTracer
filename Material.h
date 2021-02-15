//
// Created by dimasya on 09.01.2021.
//

#ifndef SHAD_CPP0_MATERIAL_H
#define SHAD_CPP0_MATERIAL_H

#include <RGB.h>

struct Material {
    Material()
        : Ka(Vector3D()),
        Kd(Vector3D()),
        Ks(Vector3D()),
        Ke(Vector3D()),
        Ns(0),
        Ni(0),
        Tr(0),
        illum(false){

    }
    Vector3D Ka;
    Vector3D Kd;
    Vector3D Ks;
    Vector3D Ke;

    double Ns;
    double Ni;
    double Tr;

    bool illum;
};

#endif  // SHAD_CPP0_MATERIAL_H
