#pragma once

#include "tuple.h"

class Matrix {

private:
    float* values = nullptr;

    inline int index(int row, int col) const {
        return col + row * size;
    }

    inline static constexpr int index4(int row, int col) {
        return col + row * 4;
    }

public:
    int size;

    inline explicit Matrix(int size) : size(size) {
        values = new float[size * size] {0};
    }

    inline Matrix(int size, const float init[]) : size(size) {
        values = new float[size * size] {0};

        std::copy(init, init + size * size, values);
    }

    inline static Matrix identity() {
        const float values[] {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

        return Matrix(4, values);
    }

    inline ~Matrix() {
        delete[] values;
    }

    inline Matrix(const Matrix &other) : Matrix(other.size, other.values) {}

    inline Matrix& operator=(const Matrix &other) {
        if (this != &other) {
            delete[] values;
            size = other.size;
            values = new float[size * size] {0};
            std::copy(other.values, other.values + size * size, values);
        }
        return *this;
    }

    inline void set(int row, int col, float value) {
        values[index(row, col)] = value;
    }

    inline float get(int row, int col) const {
        return values[index(row, col)];
    }

    inline bool operator==(const Matrix& other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size * size; i++) {
            if (!float_equal(values[i], other.values[i])) {
                return false;
            }
        }

        return true;
    }

    inline Matrix operator*(const Matrix& other) const {
        Matrix result = Matrix(4);
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.set(row, col,
                           values[index4(row, 0)] * other.values[index4(0, col)] +
                           values[index4(row, 1)] * other.values[index4(1, col)] +
                           values[index4(row, 2)] * other.values[index4(2, col)] +
                           values[index4(row, 3)] * other.values[index4(3, col)]);
            }
        }

        return result;
    }

    inline Tuple operator*(const Tuple &tuple) const {
        Tuple result = Tuple(0, 0, 0, 0);
        result.x = values[index4(0, 0)] * tuple.x + values[index4(0, 1)] * tuple.y + values[index4(0, 2)] * tuple.z + values[index4(0, 3)] * tuple.w;
        result.y = values[index4(1, 0)] * tuple.x + values[index4(1, 1)] * tuple.y + values[index4(1, 2)] * tuple.z + values[index4(1, 3)] * tuple.w;
        result.z = values[index4(2, 0)] * tuple.x + values[index4(2, 1)] * tuple.y + values[index4(2, 2)] * tuple.z + values[index4(2, 3)] * tuple.w;
        result.w = values[index4(3, 0)] * tuple.x + values[index4(3, 1)] * tuple.y + values[index4(3, 2)] * tuple.z + values[index4(3, 3)] * tuple.w;

        return result;
    }

    inline Matrix transposed() const {
        Matrix result = Matrix(size);

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                result.set(col, row, get(row, col));
            }
        }

        return result;
    }

    inline float determinant() const {
        if (size == 2)
            return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);

        float det = 0;
        for(int col = 0; col < size; col++) {
            det += get(0, col) * cofactor(0, col);
        }
        return det;
    }

    inline Matrix submatrix(int removeRow, int removeCol) const {
        Matrix result = Matrix(size - 1);

        int srcRow = 0;
        int srcCol = 0;
        for (int row = 0; row < size - 1; row++) {
            if (srcRow == removeRow)
                srcRow++;
            srcCol = 0;

            for (int col = 0; col < size - 1; col++) {
                if (srcCol == removeCol)
                    srcCol++;

                result.set(row, col, get(srcRow, srcCol));

                srcCol++;
            }

            srcRow++;
        }

        return result;
    }

    inline float minor(int row, int col) const {
        return submatrix(row, col).determinant();
    }

    inline float cofactor(int row, int col) const {
        if ((row + col) % 2 == 0) {
            return minor(row, col);
        }

        return -minor(row, col);
    }

    inline bool is_invertible() const {
        return determinant() != 0;
    }

    inline Matrix inverse() const {
        if (!is_invertible())
            throw std::domain_error("Cannot invert this matrix");

        Matrix result = Matrix(size);

        float det = determinant();
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                result.set(col, row, cofactor(row, col) / det);
            }
        }

        return result;
    }

};

inline std::ostream& operator <<(std::ostream &stream, const Matrix& matrix) {
    for (int row = 0; row < matrix.size; row++) {
        stream << "| ";
        for (int col = 0; col < matrix.size; col++) {
            stream << matrix.get(row, col);
            stream << "| ";
        }
        stream << std::endl;
    }
    return stream;
}
