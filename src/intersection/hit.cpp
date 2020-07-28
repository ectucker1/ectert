#include "hit.h"
#include <algorithm>

Hit::Hit(const Intersection &intersection, const Ray &ray, const std::vector<Intersection>& xs) : object(intersection.object) {
    t = intersection.t;

    point = ray.position(t);
    eyev = -ray.direction;
    normalv = object-> normal_at(point);

    if (normalv.dot(eyev) < 0) {
        inside = true;
        normalv = -normalv;
    }

    reflectv = ray.direction.reflect(normalv);

    // Point slightly outside object, used to prevent shadow acne
    over_point = point + normalv * 0.01;
    // Point slightly inside object, used for refraction
    under_point = point - normalv * 0.01;

    // Determine index of refraction being entered and left at this intersection
    auto containers = std::vector<std::shared_ptr<const Shape>>();
    for (const Intersection& x : xs) {
        // Set N1 when we get to the current intersection
        if (x == intersection) {
            if (containers.empty()) {
                // Air default IOR
                n1 = 1.0;
            } else {
                n1 = containers.back()->material.ior;
            }
        }

        // If the object is already in the container, then we are exiting it
        auto location = std::find(containers.begin(), containers.end(), x.object);
        if (location != containers.end()) {
            containers.erase(location);
        } else {
            containers.push_back(x.object);
        }

        // Current intersection, but now with containers changed
        if (x == intersection) {
            if (containers.empty()) {
                // Exiting into air
                n2 = 1.0;
            } else {
                n2 = containers.back()->material.ior;
            }

            // N2 found, no need to loop further
            break;
        }
    }
}
