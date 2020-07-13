#include "hit.h"

Hit::Hit(const Intersection &intersection, const Ray &ray) {
    t = intersection.t;
    object = intersection.object;

    point = ray.position(t);
    eyev = -ray.direction;
    normalv = object-> normal_at(point);

    if (normalv.dot(eyev) < 0) {
        inside = true;
        normalv = -normalv;
    }

    over_point = point + normalv * 0.01;
}
