#include "pattern.h"

#include "shapes/shape.h"

Pattern::Pattern() : _transform(Matrix::identity()), _inverse(Matrix::identity()) {}

Matrix Pattern::transform() const {
    return _transform;
}

void Pattern::transform(const Matrix &trans) {
    _transform = trans;
    _inverse = trans.inverse();
}

Matrix Pattern::inverse() const {
    return _inverse;
}

Color Pattern::sample_shape(const std::shared_ptr<const Shape>& shape, Tuple position) const {
    return sample_pattern(inverse() * shape->world_to_object(position));
}
