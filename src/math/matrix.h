#pragma once

#include "tuple.h"

class Matrix {

private:
    float* values = nullptr;

    int index(int row, int col) const;

public:
    int size;

    explicit Matrix(int size);
    Matrix(int size, const float init[]);
    static Matrix identity();

    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    void set(int row, int col, float value);
    float get(int row, int col) const;

    bool operator ==(const Matrix& other) const;

    Matrix operator *(const Matrix& other) const;
    Tuple operator *(const Tuple& other) const;

    Matrix transposed() const;

    float determinant() const;
    Matrix submatrix(int row, int col) const;
    float minor(int row, int col) const;
    float cofactor(int row, int col) const;

    bool is_invertible() const;
    Matrix inverse() const;

};

std::ostream& operator <<(std::ostream& stream, const Matrix& matrix);