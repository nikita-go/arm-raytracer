#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "core/hitable.h"
#include <vector>
#include <memory>

class HitableList : public Hitable {
  public:
    std::vector<std::shared_ptr<Hitable>> objects;

    HitableList() {}

    HitableList(std::shared_ptr<Hitable> object) {
        add(object); }

    void clear() {
        objects.clear();
    }

    void add(std::shared_ptr<Hitable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

    AABB bounding_box() const override;

    float pdf_value(const Vec3& o, const Vec3& v) const override;
    
    Vec3 random(const Vec3& o, Xoshiro128PlusPlus& rng) const override;
};

#endif // HITABLE_LIST_H