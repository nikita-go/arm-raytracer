#include "core/hitable_list.h"
#include <cstdlib>

// Checks if the ray intersects with any object in the list within the given t range
// Updates the HitRecord with the closest intersection found
bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

// Computes the axis-aligned bounding box (AABB) that encloses all objects in the list
AABB HitableList::bounding_box() const {
    if (objects.empty()) return AABB(); // Return an empty AABB if the list is empty

    AABB temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (first_box) {
            temp_box = object->bounding_box();
            first_box = false;
        } else {
            temp_box = temp_box.merge(object->bounding_box());
        }
    }

    return temp_box;
}

// Computes the probability density function (PDF) value for the given origin and direction
float HitableList::pdf_value(const Vec3& o, const Vec3& v) const {
    if (objects.empty()) return 0.0f; // No objects, so PDF is zero
    float weight = 1.0f / objects.size(); // Equal weight for each object
    float sum = 0.0f;
    for (const auto& object : objects) {
        sum += object->pdf_value(o, v);
    }
    return sum * weight; // Average the PDF values weighted by the number of objects
}

// Generates a random direction from the origin o towards one of the objects in the list
Vec3 HitableList::random(const Vec3& o, Xoshiro128PlusPlus& rng) const {
    if (objects.empty()) return Vec3(1, 0, 0); // Default direction if the list is empty

    // Select a random object from the list and delegate to its random method
    int index = static_cast<int>(rng.rand_float() * objects.size());
    return objects[index]->random(o, rng);
}