#ifndef BVH_H
#define BVH_H

#include "core/hitable.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>

// BVHNode represents a node in a Bounding Volume Hierarchy tree for efficient ray tracing
class BVHNode : public Hitable {
    std::shared_ptr<Hitable> left, right;
    AABB box;

    // Static helper function to compare Hitable objects for sorting
    static bool box_compare(const std::shared_ptr<Hitable>& a, const std::shared_ptr<Hitable>& b, int axis);

public:
    BVHNode(std::vector<std::shared_ptr<Hitable>>& objects, size_t start, size_t end);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
    AABB bounding_box() const override;
    float pdf_value(const Vec3& o, const Vec3& v) const override;
    Vec3 random(const Vec3& o) const override;
};

#endif // BVH_H