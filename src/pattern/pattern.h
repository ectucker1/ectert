#pragma once

class Shape;

#include "math/color.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include <memory>

class Pattern {

public:
    void transform(const Matrix& trans);

    Matrix inverse() const;

    Pattern();

    Color sample_shape(const std::shared_ptr<const Shape>& shape, Tuple position) const;
    virtual Color sample_pattern(Tuple position) const = 0;

    Matrix transform() const;

private:
    Matrix _transform;
    Matrix _inverse;

};
