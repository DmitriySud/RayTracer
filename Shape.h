//
// Created by dimasya on 21.01.2021.
//

#ifndef SHAD_CPP0_SHAPE_H
#define SHAD_CPP0_SHAPE_H

#include "Material.h"
class Shape{
public:
    Vector3D GetKd() const{
        return mtl->Kd;
    }

    Vector3D GetKa() const{
        return mtl->Ka;
    }

    Vector3D GetKe() const{
        return mtl->Ke;
    }

    Vector3D GetKs() const{
        return mtl->Ks;
    }

    double GetNs() const{
        return mtl->Ns;
    }

    double GetNi() const{
        return mtl->Ni;
    }

    double GetTr() const{
        return mtl->Tr;
    }

    bool IsReflecting() const{
        return mtl->illum;
    }

    virtual Vector3D GetPointColor(const Vector3D& point,
                                   const Vector3D& diffuse, const Vector3D& specular) const = 0;

    virtual Vector3D GetNorm(const Vector3D& point) const = 0;

    virtual bool Intersect(const Ray& ray, double* distance) const = 0;

    virtual Vector3D GetSurfacePoint(const Ray& ray) const  = 0;

    virtual bool GetInsideFlag() const = 0;

protected:
    Shape(Material* mtl) : mtl(mtl) {
    }


    Material* mtl;
};
#endif  // SHAD_CPP0_SHAPE_H
