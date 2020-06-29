#include "gtest/gtest.h"
#include "math/matrix.h"

TEST(MatrixTest, CreatingMatrix4) {
    float values[] {1.0f, 2.0f, 3.0f, 4.0f,
                    5.5f, 6.5f, 7.5f, 8.5f,
                    9.0f, 10.0f, 11.0f, 12.0f,
                    13.5f, 14.5f, 15.5f, 16.5f};
    Matrix matrix = Matrix(4, values);

    EXPECT_FLOAT_EQ(matrix.get(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(matrix.get(0, 3), 4.0f);
    EXPECT_FLOAT_EQ(matrix.get(1, 0), 5.5f);
    EXPECT_FLOAT_EQ(matrix.get(1, 2), 7.5f);
    EXPECT_FLOAT_EQ(matrix.get(2, 2), 11.0f);
    EXPECT_FLOAT_EQ(matrix.get(3, 0), 13.5f);
    EXPECT_FLOAT_EQ(matrix.get(3, 2), 15.5f);
}

TEST(MatrixTest, CreatingMatrix2) {
    float values[] {-3, 5,
                    1, -2};
    Matrix matrix = Matrix(2, values);

    EXPECT_FLOAT_EQ(matrix.get(0, 0), -3);
    EXPECT_FLOAT_EQ(matrix.get(0, 1), 5);
    EXPECT_FLOAT_EQ(matrix.get(1, 0), 1);
    EXPECT_FLOAT_EQ(matrix.get(1, 1), -2);
}

TEST(MatrixTest, CreatingMatrix3) {
    float values[] {-3, 5, 0,
                    1, -2, -7,
                    0, 1, 1};
    Matrix matrix = Matrix(3, values);

    EXPECT_FLOAT_EQ(matrix.get(0, 0), -3);
    EXPECT_FLOAT_EQ(matrix.get(1, 1), -2);
    EXPECT_FLOAT_EQ(matrix.get(2, 2), 1);
}

TEST(MatrixTest, ComparingEqualMatrices) {
    float values1[] {1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 8, 7, 6,
                    5, 4, 3, 2};
    float values2[] {1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 8, 7, 6,
                    5, 4, 3, 2};
    Matrix a = Matrix(4, values1);
    Matrix b = Matrix(4, values2);

    EXPECT_TRUE(a == b);
}

TEST(MatrixTest, ComparingUnequalMatrices) {
    float values1[] {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 8, 7, 6,
                     5, 4, 3, 2};
    float values2[] {2, 3, 4, 5,
                     6, 7, 8, 9,
                     8, 7, 6, 5,
                     4, 3, 2, 1};
    Matrix a = Matrix(4, values1);
    Matrix b = Matrix(4, values2);

    EXPECT_FALSE(a == b);
}

TEST(MatrixTest, MultiplyingMatrix4) {
    float values1[] {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 8, 7, 6,
                     5, 4, 3, 2};
    float values2[] {-2, 1, 2, 3,
                     3, 2, 1, -1,
                     4, 3, 6, 5,
                     1, 2, 7, 8};
    float valuesResult[] {20, 22, 50, 48,
                          44, 54, 114, 108,
                          40, 58, 110, 102,
                          16, 26, 46, 42};
    Matrix a = Matrix(4, values1);
    Matrix b = Matrix(4, values2);
    Matrix result = Matrix(4, valuesResult);

    EXPECT_TRUE(a * b == result);
}

TEST(MatrixTest, MultiplyingMatrixTuple) {
    float values[] {1, 2, 3, 4,
                    2, 4, 4, 2,
                    8, 6, 4, 1,
                    0, 0, 0, 1};
    Matrix matrix = Matrix(4, values);
    Tuple tuple = Tuple(1, 2, 3, 1);

    EXPECT_EQ(matrix * tuple, Tuple(18, 24, 33, 1));
}

TEST(MatrixTest, MultiplyingIdentityMatrix) {
    float values[] {0, 1, 2, 4,
                    1, 2, 4, 8,
                    2, 4, 8, 16,
                    4, 8, 16, 32};
    Matrix matrix = Matrix(4, values);

    EXPECT_EQ(Matrix::identity() * matrix, matrix);
}

TEST(MatrixTest, MultiplyingIdentityTuple) {
    Tuple tuple = Tuple(1, 2, 3, 4);

    EXPECT_EQ(Matrix::identity() * tuple, tuple);
}

TEST(MatrixTest, TransposingMatrices) {
    float values[] {0, 9, 3, 0,
                    9, 8, 0, 8,
                    1, 8, 5, 3,
                    0, 0, 5, 8};
    float expected[] {0, 9, 1, 0,
                      9, 8, 8, 0,
                      3, 0, 5, 5,
                      0, 8, 3, 8};
    Matrix matrix = Matrix(4, values);

    EXPECT_EQ(matrix.transposed(), Matrix(4, expected));
}

TEST(MatrixTest, TransposingIdentity) {
    EXPECT_EQ(Matrix::identity().transposed(), Matrix::identity());
}

TEST(MatrixTest, Determinant2x2) {
    float values[] {1, 5,
                    -3, 2};
    Matrix matrix = Matrix(2, values);

    EXPECT_FLOAT_EQ(matrix.determinant(), 17);
}

TEST(MatrixTest, Submatrix4x4) {
    float values[] {-6, 1, 1, 6,
                    -8, 5, 8, 6,
                    -1, 0, 8, 2,
                    -7, 1, -1, 1};
    float expected[] {-6, 1, 6,
                      -8, 8, 6,
                      -7, -1, 1};
    Matrix matrix = Matrix(4, values);

    EXPECT_EQ(matrix.submatrix(2, 1), Matrix(3, expected));
}

TEST(MatrixTest, Submatrix3x3) {
    float values[] {1, 5, 0,
                    -3, 2, 7,
                    0, 6, -3};
    float expected[] {-3, 2,
                      0, 6};
    Matrix matrix = Matrix(3, values);

    EXPECT_EQ(matrix.submatrix(0, 2), Matrix(2, expected));
}

TEST(MatrixTest, Minor3x3) {
    float values[] {3, 5, 0,
                    2, -1, -7,
                    6, -1, 5};
    Matrix a = Matrix(3, values);
    Matrix b = a.submatrix(1, 0);

    EXPECT_FLOAT_EQ(b.determinant(), 25);
    EXPECT_FLOAT_EQ(a.minor(1, 0), 25);
}

TEST(MatrixTest, Cofactor3x3) {
    float values[] {3, 5, 0,
                    2, -1, -7,
                    6, -1, 5};
    Matrix matrix = Matrix(3, values);

    EXPECT_FLOAT_EQ(matrix.minor(0, 0), -12);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 0), -12);
    EXPECT_FLOAT_EQ(matrix.minor(1, 0), 25);
    EXPECT_FLOAT_EQ(matrix.cofactor(1, 0), -25);
}

TEST(MatrixTest, Determinant3x3) {
    float values[] {1, 2, 6,
                    -5, 8, -4,
                    2, 6, 4};
    Matrix matrix = Matrix(3, values);

    EXPECT_FLOAT_EQ(matrix.cofactor(0, 0), 56);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 1), 12);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 2), -46);
    EXPECT_FLOAT_EQ(matrix.determinant(), -196);
}

TEST(MatrixTest, Determinant4x4) {
    float values[] {-2, -8, 3, 5,
                    -3, 1, 7, 3,
                    1, 2, -9, 6,
                    -6, 7, 7, -9};
    Matrix matrix = Matrix(4, values);

    EXPECT_FLOAT_EQ(matrix.cofactor(0, 0), 690);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 1), 447);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 2), 210);
    EXPECT_FLOAT_EQ(matrix.cofactor(0, 3), 51);
    EXPECT_FLOAT_EQ(matrix.determinant(), -4071);
}

TEST(MatrixTest, TestingInvertible) {
    float values[] {6, 4, 4, 4,
                    5, 5, 7, 6,
                    4, -9, 3, -7,
                    9, 1, 7, -6};
    Matrix matrix = Matrix(4, values);

    EXPECT_FLOAT_EQ(matrix.determinant(), -2120);
    EXPECT_TRUE(matrix.is_invertible());
}

TEST(MatrixTest, TestingNotInvertible) {
    float values[] {-4, 2, -2, -3,
                    9, 6, 2, 6,
                    0, -5, 1, -5,
                    0, 0, 0, 0};
    Matrix matrix = Matrix(4, values);

    EXPECT_FLOAT_EQ(matrix.determinant(), 0);
    EXPECT_FALSE(matrix.is_invertible());
}

TEST(MatrixTest, Inversion) {
    float values[] {-5, 2, 6, -8,
                    1, -5, 1, 8,
                    7, 7, -6, -7,
                    1, -3, 7, 4};
    float expected[] { 0.21805f, 0.45113f, 0.24060f, -0.04511f,
                       -0.80827f, -1.45677f, -0.44361f, 0.52068f,
                       -0.07895f, -0.22368f, -0.05263f, 0.19737f,
                       -0.52256f, -0.81391f, -0.30075f, 0.30639f};
    Matrix a = Matrix(4, values);
    Matrix b = a.inverse();

    EXPECT_FLOAT_EQ(a.determinant(), 532);
    EXPECT_FLOAT_EQ(a.cofactor(2, 3), -160);
    EXPECT_FLOAT_EQ(b.get(3, 2), -160.0f / 532.0f);
    EXPECT_FLOAT_EQ(a.cofactor(3, 2), 105);
    EXPECT_FLOAT_EQ(b.get(2, 3), 105.0f / 532.0f);
    EXPECT_EQ(b, Matrix(4, expected));
}

TEST(MatrixTest, Inversion2) {
    float values[] {8, -5, 9, 2,
                    7, 5, 6, 1,
                    -6, 0, 9, 6,
                    -3, 0, -9, -4};
    float expected[] {-0.15385f, -0.15385f, -0.28205f, -0.53846f,
                      -0.07692f, 0.12308f, 0.02564f, 0.03077f,
                      0.35897f, 0.35897f, 0.43590f, 0.92308f,
                      -0.69231f, -0.69231f, -0.76923f, -1.92308f};
    Matrix matrix = Matrix(4, values);

    EXPECT_EQ(matrix.inverse(), Matrix(4, expected));
}

TEST(MatrixTest, Inversion3) {
    float values[] {9, 3, 0, 9,
                    -5, -2, -6, -3,
                    -4, 9, 6, 4,
                    -7, 6, 6, 2};
    float expected[] {-0.04074f, -0.07778f, 0.14444f, -0.22222f,
                      -0.07778f, 0.03333f, 0.36667f, -0.33333f,
                      -0.02901f, -0.14630f, -0.10926f, 0.12963f,
                      0.17778f, 0.06667f, -0.26667f, 0.33333f};
    Matrix matrix = Matrix(4, values);

    EXPECT_EQ(matrix.inverse(), Matrix(4, expected));
}

TEST(MatrixTest, MultiplyingInverse) {
    float valuesA[] {3, -9, 7, 3,
                     3, -8, 2, -9,
                     -4, 4, 4, 1,
                     -6, 5, -1, 1};
    float valuesB[] {8, 2, 2, 2,
                     3, -1, 7, 0,
                     7, 0, 5, 4,
                     6, -2, 0, 5};
    Matrix a = Matrix(4, valuesA);
    Matrix b = Matrix(4, valuesB);
    Matrix c = a * b;
    Matrix d = b * a;

    EXPECT_EQ(c * b.inverse(), a);
    EXPECT_EQ(d * a.inverse(), b);
}
