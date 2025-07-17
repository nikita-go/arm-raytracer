#include "core/world.h"

// Constructor for World class, initializing with objects and lights
World::World(const std::vector<std::shared_ptr<Hitable>>& objects, const std::vector<std::shared_ptr<Hitable>>& lts)
    : lights(lts) {
    // Create a copy of the input objects vector
    std::vector<std::shared_ptr<Hitable>> objs = objects;

    // Build a BVH tree from the objects
    root = std::make_shared<BVHNode>(objs, 0, objs.size());
}

// Check if a ray intersects with any object in the world
bool World::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    // Delegate to the root BVH node
    return root->hit(r, t_min, t_max, rec);
}

AABB World::bounding_box() const {
    // Return the bounding box of the root BVH node
    return root->bounding_box();
}

// Select a random light from the list of lights
std::shared_ptr<Hitable> World::get_random_light(Xoshiro128PlusPlus& rng) const {
    if (lights.empty()) return nullptr;
    return lights[rng.next() % lights.size()];
}