//
// Created by dimasya on 21.01.2021.
//

#ifndef SHAD_CPP0_SPHERE_H
#define SHAD_CPP0_SPHERE_H

#include "Vector3D.h"
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(double radius, const Vector3D& center, Material* mtl)
        : Shape(mtl), radius(radius), center(center) {
    }

    explicit Sphere()
        : Shape(nullptr), radius(0), center(Vector3D()){

    }

    Vector3D GetPointColor(const Vector3D& point, const Vector3D& diffuse,
                           const Vector3D& specular) const override {
        return GetKa() + GetKe() + GetKd().ElementMult(diffuse) + GetKs().ElementMult(specular);
    }

    Vector3D GetNorm(const Vector3D& point) const override{
        return (point - center).Normalize();
    }

    bool Intersect(const Ray& ray, double* distance) const override{
        auto point = GetSurfacePoint(ray);
        if (distance != nullptr){
            *distance = (point - ray.point).GetModule();
        }
        return point != Vector3D(true);
    }

    Vector3D GetSurfacePoint(const Ray& ray) const override{
        Vector3D from_center = ray.point - center;
        double coef_a = 1;
        double coef_b = 2 * (from_center) * ray.direction;
        double coef_c = from_center * from_center - radius * radius;

        double discriminant = (coef_b / 2) * (coef_b / 2) - coef_a * coef_c;
        if (discriminant < 0){
            return Vector3D(true);
        }
        discriminant = std::sqrt(discriminant);
        double root1 = (-coef_b/2 + discriminant) / coef_a;
        double root2 = (-coef_b/2 - discriminant) / coef_a;
        double min_t = MinPositive(root1, root2);

        if (min_t < 0){
            return Vector3D(true);
        }
        return ray.point + min_t * ray.direction;
    }

    bool GetInsideFlag() const override{
        return true;
    }
public:
    double radius;
    Vector3D center;
private:
    static double MinPositive(double a, double b){
        return (a >= 0 && b < 0) ? a :
                (a < 0 && b >= 0) ? b :
                std::min(a,b);
    }
};

#endif  // SHAD_CPP0_SPHERE_H
