#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils/ray.h"
#include "utils/rng.h"
#include "core/hitable.h"

// Material base class
class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered, float& pdf, Xoshiro128PlusPlus& rng) const = 0;

    virtual Vec3 emitted(float u, float v, const Vec3& p) const {
        return Vec3(0,0,0);
    }

    virtual float scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const {
        return 0;
    }
};

#endif // MATERIAL_H