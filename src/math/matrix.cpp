#include "matrix.h"
#include <stdexcept>
#include "float_util.h"

Matrix::Matrix(int size) : size(size) {
    values = new float[size * size] {0};
}

Matrix::Matrix(int size, const float init[]) : size(size) {
    values = new float[size * size] {0};

    std::copy(init, init + size * size, values);
}

Matrix Matrix::identity() {
    const float values[] {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    return Matrix(4, values);
}

Matrix::~Matrix() {
    delete[] values;
}

int Matrix::index(int row, int col) const {
    return col + row * size;
}

void Matrix::set(int row, int col, float value) {
    values[index(row, col)] = value;
}

float Matrix::get(int row, int col) const {
    return values[index(row, col)];
}

bool Matrix::operator==(const Matrix& other) const {
    if (size != other.size) {
        return false;
    }

    for (int i = 0; i < size * size; i++) {
        float a = values[i];
        float b = other.values[i];
        if (!float_equal(values[i], other.values[i])) {
            return false;
        }
    }

    return true;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (size != 4 || other.size != 4) {
        throw std::invalid_argument("Multiplied matrices must be 4x4");
    }

    Matrix result = Matrix(4);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.set(row, col,
                    get(row, 0) * other.get(0, col) +
                    get(row, 1) * other.get(1, col) +
                    get(row, 2) * other.get(2, col) +
                    get(row, 3) * other.get(3, col));
        }
    }

    return result;
}

Tuple Matrix::operator*(const Tuple &tuple) const {
    if (size != 4) {
        throw std::invalid_argument("Multiplied matrices must be 4x4");
    }

    Tuple result = Tuple(0, 0, 0, 0);
    result.x = get(0, 0) * tuple.x + get(0, 1) * tuple.y + get(0, 2) * tuple.z + get(0, 3) * tuple.w;
    result.y = get(1, 0) * tuple.x + get(1, 1) * tuple.y + get(1, 2) * tuple.z + get(1, 3) * tuple.w;
    result.z = get(2, 0) * tuple.x + get(2, 1) * tuple.y + get(2, 2) * tuple.z + get(2, 3) * tuple.w;
    result.w = get(3, 0) * tuple.x + get(3, 1) * tuple.y + get(3, 2) * tuple.z + get(3, 3) * tuple.w;

    return result;
}

Matrix Matrix::transposed() const {
    Matrix result = Matrix(size);

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result.set(col, row, get(row, col));
        }
    }

    return result;
}

float Matrix::determinant() const {
    if (size == 2)
        return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);

    float det = 0;
    for(int col = 0; col < size; col++) {
        det += get(0, col) * cofactor(0, col);
    }
    return det;
}

Matrix Matrix::submatrix(int removeRow, int removeCol) const {
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

float Matrix::minor(int row, int col) const {
    return submatrix(row, col).determinant();
}

float Matrix::cofactor(int row, int col) const {
    if ((row + col) % 2 == 0) {
        return minor(row, col);
    }

    return -minor(row, col);
}

bool Matrix::is_invertible() const {
    return determinant() != 0;
}

Matrix Matrix::inverse() const {
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

std::ostream& operator <<(std::ostream &stream, const Matrix& matrix) {
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
