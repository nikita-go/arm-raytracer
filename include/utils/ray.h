#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Ray
struct Ray {
    Vec3 o, d;

    Ray() = default;
    Ray(const Vec3& oo, const Vec3& dd) : o(oo), d(dd.norm()) {}
};

#endif // RAY_H