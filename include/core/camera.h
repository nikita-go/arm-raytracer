#ifndef CAMERA_H
#define CAMERA_H

#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/utils.h"
#include <cmath>

// Camera
class Camera {
    Vec3 origin, lower_left, horizontal, vertical, u, v, w;
    float lens_radius;
public:
    // Initialize camera with position, direction, and lens settings
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist);
    // Generate a ray through pixel (s, t) with depth of field
    Ray get_ray(float s, float t, Xoshiro128PlusPlus& rng) const;
};

#endif // CAMERA_H