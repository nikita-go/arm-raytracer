#include "utils/utils.h"
#include <cmath>

// Utilities
Vec3 random_in_unit_sphere(Xoshiro128PlusPlus& rng) {
    float theta = 2 * M_PI * rng.rand_float();
    float phi = acos(2 * rng.rand_float() - 1);
    float r = pow(rng.rand_float(), 1.0f/3);
    return Vec3(r * sin(phi) * cos(theta), r * sin(phi) * sin(theta), r * cos(phi));
}

Vec3 random_in_unit_disk(Xoshiro128PlusPlus& rng) {
    Vec3 p;
    do {
        p = Vec3(rng.rand_float() * 2 - 1, rng.rand_float() * 2 - 1, 0);
    } while (p.dot(p) >= 1);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - n * (2 * v.dot(n));
}