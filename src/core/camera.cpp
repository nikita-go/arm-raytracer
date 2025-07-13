#include "core/camera.h"

// Camera constructor: sets up viewport and lens
Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180; // Convert vfov to radians
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).norm(); // Camera direction
    u = vup.cross(w).norm(); // Right vector
    v = w.cross(u); // Up vector
    lower_left = origin - u * (half_width * focus_dist) - v * (half_height * focus_dist) - w * focus_dist; // Viewport corner
    horizontal = u * (2 * half_width * focus_dist); // Horizontal span
    vertical = v * (2 * half_height * focus_dist); // Vertical span
}

// Generate ray with depth of field effect
Ray Camera::get_ray(float s, float t, Xoshiro128PlusPlus& rng) const {
    Vec3 rd = random_in_unit_disk(rng) * lens_radius; // Random lens offset
    Vec3 offset = u * rd.x + v * rd.y;
    return Ray(origin + offset, (lower_left + horizontal * s + vertical * t - origin - offset).norm());
}