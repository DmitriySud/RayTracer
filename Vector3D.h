#ifndef SHAD_CPP0_VECTOR_3D_H
#define SHAD_CPP0_VECTOR_3D_H

#include <iostream>
#include <cmath>


struct Vector3D {
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {
    }

    Vector3D(const std::array<double, 3>& vec)
        : x(vec[0]), y(vec[1]), z(vec[2]){

    }

    explicit Vector3D(bool fake = false)
        : x(fake ? std::numeric_limits<double>().min() : 0), y(x), z(x) {
    }

    double operator*(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D operator/(double alpha){
        return *this * (1/alpha);
    }

    Vector3D operator*(double alpha) const {
        return Vector3D(x * alpha, y * alpha, z * alpha);
    }

    friend Vector3D operator*(double alpha, const Vector3D& vec){
        return vec * alpha;
    }

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D& operator/=(double alpha) {
        x /= alpha;
        y /= alpha;
        z /= alpha;
        return *this;
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3D& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    Vector3D ElementMult(const Vector3D& other) const{
        return {x * other.x, y * other.y, z * other.z};
    }

    double GetModule() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    static double Distance(const Vector3D& lhs, const Vector3D& rhs) {
        return (lhs - rhs).GetModule();
    }

    Vector3D operator^(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        -(x * other.z - z * other.x),
                        x * other.y - y * other.x);
    }

    double operator[](int idx) const {
        if(idx == 0){
            return x;
        } else if (idx == 1){
            return y;
        } else if (idx == 2){
            return z;
        }
        throw "index out of range";
    }

    Vector3D Normalize() const{
        double norm = GetModule();
        return Vector3D(x / norm, y / norm, z / norm);
    }



    double x;
    double y;
    double z;
};

std::istream& operator>> (std::istream& in, Vector3D& vector){
    in >> vector.x >>vector.y >> vector.z;
    return in;
}

#endif  // SHAD_CPP0_VECTOR_3D_H
