//
// Created by dimasya on 08.01.2021.
//

#ifndef SHAD_CPP0_TRIANGLE_H
#define SHAD_CPP0_TRIANGLE_H

#include "Vertex.h"
#include "Ray.h"
#include "Shape.h"

class Triangle : public Shape {
public:
    explicit Triangle()
        : Shape(nullptr),
          p1_(Vector3D()),
          p2_(Vector3D()),
          p3_(Vector3D()),
          norm_(Vector3D(1, 0, 0)),
          coef_d_(0),
          custom_normals_(false) {
    }

    Triangle(Vertex p1, Vertex p2, Vertex p3, Material* mtl)
        : Shape(mtl),
          p1_(p1),
          p2_(p2),
          p3_(p3),
          norm_((p2_.point - p1_.point) ^ (p3_.point - p1.point)),
          coef_d_(-(p1_.point * norm_)) ,
          custom_normals_(p1_.has_normal || p2_.has_normal || p3_.has_normal){
        double norm_len = norm_.GetModule();

        coef_d_ /= norm_len;
        norm_ /= norm_len;

        if (custom_normals_){
            if(!p1_.has_normal){
                p1_.SetNorm(norm_);
            }
            if(!p2_.has_normal){
                p2_.SetNorm(norm_);
            }
            if(!p3_.has_normal){
                p3_.SetNorm(norm_);
            }
        }
    }

    Vector3D GetSurfacePoint(const Vector3D& vector, bool* reverse) const {
        double alpha = -coef_d_ / (norm_ * vector);
        *reverse = alpha < 0;
        return vector * alpha;
    }

    Vector3D GetSurfacePoint(const Ray& ray) const override {
        double num = coef_d_ + norm_ * ray.point, denom = norm_ * ray.direction;
        return ray.point + (-num / denom) * ray.direction;
    }

    bool IsPointInTriangle(const Vector3D& pt) const {
        Vector3D first = (p2_.point - p1_.point) ^ (pt - p1_.point),
                 second = (p3_.point - p2_.point) ^ (pt - p2_.point),
                 third = (p1_.point - p3_.point) ^ (pt - p3_.point);

        double coef_1 = (norm_.x != 0)   ? first.x / norm_.x
                        : (norm_.y != 0) ? first.y / norm_.y
                        : (norm_.z != 0) ? first.z / norm_.z
                                         : 1,
               coef_2 = (norm_.x != 0)   ? second.x / norm_.x
                        : (norm_.y != 0) ? second.y / norm_.y
                        : (norm_.z != 0) ? second.z / norm_.z
                                         : 1,
               coef_3 = (norm_.x != 0)   ? third.x / norm_.x
                        : (norm_.y != 0) ? third.y / norm_.y
                        : (norm_.z != 0) ? third.z / norm_.z
                                         : 1;

        return (coef_1 >= 0 && coef_2 >= 0 && coef_3 >= 0) ||
               (coef_1 <= 0 && coef_2 <= 0 && coef_3 <= 0);
    }

    bool Intersect(const Vector3D& vector) const {
        bool reverse = false;

        Vector3D point = GetSurfacePoint(vector, &reverse);
        return !reverse && IsPointInTriangle(point);
    }

    bool Intersect(const Ray& ray, double* distance) const override {
        double num = coef_d_ + norm_ * ray.point, denom = norm_ * ray.direction;

        *distance = std::numeric_limits<double>().max();
        if (denom == 0) {
            return false;
        }

        double dist = -num / denom;
        if (dist < 0) {
            return false;
        }

        Vector3D intersect_point = ray.point + dist * ray.direction;
        *distance = dist;

        return IsPointInTriangle(intersect_point);
    }

    double GetSquare() const {
        Vector3D vec1 = p2_.point - p1_.point, vec2 = p3_.point - p1_.point;
        return (vec1 ^ vec2).GetModule() / 2;
    }

    Vector3D GetNorm(const Vector3D& point) const override {
        if (custom_normals_){
            Vector3D coord = GetBarycentricCoordinate(point);
            return coord.x * p1_.norm + coord.y * p2_.norm + coord.z * p3_.norm;
        }

        return norm_;
    }

    Vector3D GetBarycentricCoordinate(const Vector3D& point) const {
        double square = GetSquare();
        double u = ((p2_.point - p1_.point) ^ (point - p1_.point)).GetModule() / 2 / square,
               v = ((p3_.point - p2_.point) ^ (point - p2_.point)).GetModule() / 2 / square,
               w = 1 - u - v;
        return {u, v, w};
    }

    Vector3D GetPointColor(const Vector3D& point, const Vector3D& diffuse,
                           const Vector3D& specular) const override {
        return GetKa() + GetKe() + GetKd().ElementMult(diffuse) + GetKs().ElementMult(specular);
    }

    bool GetInsideFlag() const override {
        return false;
    }

private:
    Vertex p1_;
    Vertex p2_;
    Vertex p3_;

    // TODO : убрать все коэффициенты кроме d
    Vector3D norm_;
    double coef_d_;

    bool custom_normals_;
};

#endif SHAD_CPP0_TRIANGLE_H