#ifndef HITABLE_H
#define HITABLE_H

#include "utils/ray.h"
#include "utils/rng.h"
#include "core/aabb.h"
#include <memory>

// Forward declarations
class Material;

// Hit Record
struct HitRecord {
    float t;
    Vec3 p, normal;
    std::shared_ptr<Material> mat;
    bool front_face;
    float u, v;
};

// Hitable base class
class Hitable {
public:
    virtual ~Hitable() = default;

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;

    virtual AABB bounding_box() const = 0;

    virtual float pdf_value(const Vec3& o, const Vec3& v) const {
        return 0;
    }

    virtual Vec3 random(const Vec3& o, Xoshiro128PlusPlus& rng) const {
        return Vec3(1, 0, 0);
    }
};

#endif // HITABLE_H