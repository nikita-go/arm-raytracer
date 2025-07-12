#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Ray
struct Ray {
    Vec3 o, d, inv_d;

    Ray() = default;
    Ray(const Vec3& oo, const Vec3& dd) : o(oo), d(dd.norm()) {
        inv_d = Vec3(1.0f / d.x, 1.0f / d.y, 1.0f / d.z);
    }
};

#endif // RAY_H