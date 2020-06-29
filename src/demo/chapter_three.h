#pragma once

#include "math/matrix.h"
#include <iostream>

void run_chapter_three() {
    std::cout << "Inverse of identity" << std::endl;
    std::cout << Matrix::identity().inverse();

    float values[] {8, -5, 9, 2,
                    7, 5, 6, 1,
                    -6, 0, 9, 6,
                    -3, 0, -9, -4};
    Matrix invertible = Matrix(4, values);

    std::cout << "Self by inverse" << std::endl;
    std::cout << invertible * invertible.inverse() << std::endl;

    std::cout << "Inverse of Transpose VS Transpose of Inverse" << std::endl;
    std::cout << invertible.transposed().inverse();
    std::cout << "VS" << std::endl;
    std::cout << invertible.inverse().transposed();

    Matrix nearIdentity = Matrix::identity();
    nearIdentity.set(0, 1, 2);
    Tuple tuple = Tuple::point(1, 2, 3);

    std::cout << "Near identity times tuple" << std::endl;
    std::cout << nearIdentity * tuple;
}