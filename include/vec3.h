#ifndef VEC3_H
#define VEC3_H

// NEON-accelerated Vec3
struct alignas(16) Vec3 {
    float x, y, z, w = 0;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
};

#endif // VEC3_H