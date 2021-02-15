#pragma once

#include <vector>
#include "Vector3D.h"

class Matrix44 {
public:
    explicit Matrix44(double n) : Matrix44(n, n) {
    }

    Matrix44(double n, double m)
        : matrix_(std::vector<std::vector<double>>(n, std::vector<double>(m, 0))) {
    }
    explicit Matrix44(std::vector<std::vector<double>> base)
        : matrix_(std::vector<std::vector<double>>(base)) {
    }

    Matrix44(const Vector3D& eye, const Vector3D& target) {
        Vector3D xaxis, yaxis, zaxis = (eye - target).Normalize();

        if (zaxis.x == 0 && zaxis.z == 0) {
            Vector3D right = {1, 0, 0};
            yaxis = (right ^ zaxis).Normalize();  // forward x right = up
            xaxis = (yaxis ^ zaxis).Normalize();              // up x forward = right
        } else {
            Vector3D up = {0, 1, 0};
            xaxis = (up ^ zaxis).Normalize();
            yaxis = (xaxis ^ zaxis).Normalize();
        }

        matrix_ = {{xaxis.x, yaxis.x, zaxis.x, 0},
                   {xaxis.y, yaxis.y, zaxis.y, 0},
                   {xaxis.z, yaxis.z, zaxis.z, 0},
                   {eye.x, eye.y, eye.z, 1}};

        Inv33();
    }

    void Inv33() {
        double det =
            matrix_[0][0] * (matrix_[1][1] * matrix_[2][2] - matrix_[1][2]* matrix_[2][1]) -
            matrix_[0][1] * (matrix_[1][0] * matrix_[2][2] - matrix_[1][2]* matrix_[2][0]) +
            matrix_[0][2] * (matrix_[1][0] * matrix_[2][1] - matrix_[1][1]* matrix_[2][0]);
        double invdet = 1 / det;
        std::vector<std::vector<double>> inv(3, std::vector<double>(3));

        inv[0][0] = matrix_[1][1]* matrix_[2][2] - matrix_[2][1]* matrix_[1][2];
        inv[0][1] = matrix_[0][2]* matrix_[2][1] - matrix_[0][1]* matrix_[2][2];
        inv[0][2] = matrix_[0][1]* matrix_[1][2] - matrix_[0][2]* matrix_[1][1];
        inv[1][0] = matrix_[1][2]* matrix_[2][0] - matrix_[1][0]* matrix_[2][2];
        inv[1][1] = matrix_[0][0]* matrix_[2][2] - matrix_[0][2]* matrix_[2][0];
        inv[1][2] = matrix_[1][0]* matrix_[0][2] - matrix_[0][0]* matrix_[1][2];
        inv[2][0] = matrix_[1][0]* matrix_[2][1] - matrix_[2][0]* matrix_[1][1];
        inv[2][1] = matrix_[2][0]* matrix_[0][1] - matrix_[0][0]* matrix_[2][1];
        inv[2][2] = matrix_[0][0]* matrix_[1][1] - matrix_[1][0]* matrix_[0][1];

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix_[i][j] = inv[i][j] * invdet;
            }
        }
    }

    size_t Rows() const {
        return matrix_.size();
    }

    size_t Columns() const {
        return matrix_[0].size();
    }

    double& operator()(int i, int j) {
        return matrix_[i][j];
    }

    double operator()(int i, int j) const {
        return matrix_[i][j];
    }

    Matrix44 operator-(const Matrix44& b) const {
        Matrix44 res(this->matrix_);

        return res -= b;
    }

    Matrix44& operator-=(const Matrix44& b) {
        for (int row = 0; row < Rows(); ++row) {
            for (int col = 0; col < Columns(); ++col) {
                matrix_[row][col] -= b(row, col);
            }
        }
        return *this;
    }

    Matrix44 operator+(const Matrix44& b) const {
        Matrix44 res(this->matrix_);

        return res += b;
    }

    Matrix44& operator+=(const Matrix44& b) {
        for (int row = 0; row < Rows(); ++row) {
            for (int col = 0; col < Columns(); ++col) {
                matrix_[row][col] += b(row, col);
            }
        }
        return *this;
    }

    Matrix44& operator*=(const Matrix44& b) {
        this->matrix_ = (*this * b).matrix_;
        return *this;
    }

    Matrix44 operator*(const Matrix44& b) const {
        Matrix44 result(Rows(), b.Columns());
        for (int row = 0; row < Rows(); ++row) {
            for (int col = 0; col < b.Columns(); ++col) {
                for (int row_b = 0; row_b < b.Rows(); ++row_b) {
                    result(row, col) += matrix_[row][row_b] * b(row_b, col);
                }
            }
        }

        return result;
    }

    Vector3D MultVec(const Vector3D& vec) const {
        double a, b, c, w;

        a = vec[0] * matrix_[0][0] + vec[1] * matrix_[1][0] + vec[2] * matrix_[2][0] +
            matrix_[3][0];
        b = vec[0] * matrix_[0][1] + vec[1] * matrix_[1][1] + vec[2] * matrix_[2][1] +
            matrix_[3][1];
        c = vec[0] * matrix_[0][2] + vec[1] * matrix_[1][2] + vec[2] * matrix_[2][2] +
            matrix_[3][2];
        w = vec[0] * matrix_[0][3] + vec[1] * matrix_[1][3] + vec[2] * matrix_[2][3] +
            matrix_[3][3];

        return Vector3D(a / w, b / w, c / w);
    }

    Vector3D MultDir(const Vector3D& vec) const {
        double a, b, c;

        a = vec[0] * matrix_[0][0] + vec[1] * matrix_[1][0] + vec[2] * matrix_[2][0];
        b = vec[0] * matrix_[0][1] + vec[1] * matrix_[1][1] + vec[2] * matrix_[2][1];
        c = vec[0] * matrix_[0][2] + vec[1] * matrix_[1][2] + vec[2] * matrix_[2][2];

        return Vector3D(a, b, c);
    }

private:
    std::vector<std::vector<double>> matrix_;
};

Matrix44 Transpose(const Matrix44& a) {
    Matrix44 res(a.Columns(), a.Rows());
    for (int row = 0; row < a.Rows(); ++row) {
        for (int col = 0; col < a.Columns(); ++col) {
            res(col, row) = a(row, col);
        }
    }

    return res;
}
Matrix44 Identity(size_t n) {
    Matrix44 res(n, n);
    for (int row = 0; row < n; ++row) {
        res(row, row) = 1;
    }

    return res;
}
