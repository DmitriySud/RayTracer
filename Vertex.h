//
// Created by dimasya on 09.01.2021.
//

#ifndef SHAD_CPP0_VERTEX_H
#define SHAD_CPP0_VERTEX_H


#include <Vector3D.h>
#include <Material.h>

struct Vertex{
    Vertex(const Vector3D& coord)
        : point(coord), has_normal(false), norm(Vector3D()) {
    }

    Vertex(const Vector3D& coord, const Vector3D& norm)
        : point(coord), has_normal(true), norm(norm.Normalize()) {
    }

    Vertex(const Vertex& other)
        : point(other.point), has_normal(other.has_normal), norm(other.norm){
    }

    void SetNorm(const Vector3D& normal){
        has_normal = true;
        norm = normal;
    }

    Vector3D point;
    bool has_normal;
    Vector3D norm;
};

#endif  // SHAD_CPP0_VERTEX_H
