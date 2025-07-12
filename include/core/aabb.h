#ifndef AABB_H
#define AABB_H

#include "utils/vec3.h"
#include "utils/constants.h"

// Axis-Aligned Bounding Box with NEON-accelerated operations
struct alignas(64) AABB {
    Vec3 min, max;

    // Initializes to given bounds or an inverted box by default
    AABB(const Vec3& mi = Vec3(INF, INF, INF), const Vec3& ma = Vec3(-INF, -INF, -INF))
        : min(mi), max(ma) {}
};

#endif // AABB_H