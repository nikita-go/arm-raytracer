#ifndef WORLD_H
#define WORLD_H

#include "core/hitable.h"
#include "core/bvh.h"
#include "utils/rng.h"
#include <vector>
#include <memory>
#include <cstdlib>

// World
class World : public Hitable {
    std::shared_ptr<BVHNode> root;
    std::vector<std::shared_ptr<Hitable>> lights;
public:
    World(const std::vector<std::shared_ptr<Hitable>>& objects, const std::vector<std::shared_ptr<Hitable>>& lts);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
    AABB bounding_box() const override;
    std::shared_ptr<Hitable> get_random_light(Xoshiro128PlusPlus& rng) const;
};

#endif // WORLD_H