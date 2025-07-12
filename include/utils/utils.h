#ifndef UTILS_H
#define UTILS_H

#include "vec3.h"
#include "rng.h"

// Utility functions (forward declarations)
struct Vec3;
struct Ray;
Vec3 random_in_unit_sphere(Xoshiro128PlusPlus& rng);
Vec3 random_in_unit_disk(Xoshiro128PlusPlus& rng);
Vec3 reflect(const Vec3& v, const Vec3& n);

#endif // UTILS_H