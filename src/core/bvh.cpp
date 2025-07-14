#include "core/bvh.h"

// Compare two Hitable objects based on the specified axis of their bounding boxes
bool BVHNode::box_compare(const std::shared_ptr<Hitable>& a, const std::shared_ptr<Hitable>& b, int axis) {
    AABB box_a = a->bounding_box();
    AABB box_b = b->bounding_box();
    return (&box_a.min.x)[axis] < (&box_b.min.x)[axis];
}

// Construct a BVH node from a list of Hitable objects between start and end indices
BVHNode::BVHNode(std::vector<std::shared_ptr<Hitable>>& objects, size_t start, size_t end) {
    std::vector<std::shared_ptr<Hitable>> objs = objects;
    size_t count = end - start;
    if (count == 1) {
        // If there is only one object, set both left and right to that object
        left = right = objs[start];
    } else if (count == 2) {
        // If there are two objects, set left and right accordingly
        left = objs[start];
        right = objs[start + 1];
    } else {
        // For more than two objects, determine the axis with the largest extent in the centroid bounding box
        AABB centroid_bounds;
        for (size_t i = start; i < end; i++) {
            centroid_bounds = centroid_bounds.merge(objs[i]->bounding_box());
        }
        int axis = 0;
        float max_extent = 0;
        for (int a = 0; a < 3; a++) {
            float extent = (&centroid_bounds.max.x)[a] - (&centroid_bounds.min.x)[a];
            if (extent > max_extent) {
                max_extent = extent;
                axis = a;
            }
        }

        // Sort the objects along the chosen axis
        auto comparator = [axis](const std::shared_ptr<Hitable>& a, const std::shared_ptr<Hitable>& b) {
            return box_compare(a, b, axis);
        };
        std::sort(objs.begin() + start, objs.begin() + end, comparator);

        // Use the Surface Area Heuristic (SAH) to find the best split position
        float min_cost = INF;
        size_t best_mid = start + 1;
        AABB full_box = centroid_bounds;
        float full_sa = (full_box.max - full_box.min).length();
        for (size_t mid = start + 1; mid < end; mid++) {
            AABB left_box(Vec3(INF,INF,INF), Vec3(-INF,-INF,-INF));
            AABB right_box = left_box;
            for (size_t i = start; i < mid; ++i) left_box = left_box.merge(objs[i]->bounding_box());
            for (size_t i = mid; i < end; ++i) right_box = right_box.merge(objs[i]->bounding_box());
            float left_sa = (left_box.max - left_box.min).length();
            float right_sa = (right_box.max - right_box.min).length();
            float cost = 0.125f + (mid - start) * left_sa / full_sa + (end - mid) * right_sa / full_sa;
            if (cost < min_cost) {
                min_cost = cost;
                best_mid = mid;
            }
        }
        // Recursively create left and right child nodes
        left = std::make_shared<BVHNode>(objs, start, best_mid);
        right = std::make_shared<BVHNode>(objs, best_mid, end);
    }
    // Compute the bounding box of this node by merging the bounding boxes of the left and right children
    box = left->bounding_box().merge(right->bounding_box());
}

// Check if the ray intersects with this BVH node
// First, check the bounding box, then the children
bool BVHNode::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    float box_tmin, box_tmax;
    if (!box.intersect(r, box_tmin, box_tmax)) return false;
    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);
    return hit_left || hit_right;
}

AABB BVHNode::bounding_box() const {
    return box;
}

// Compute the probability density function value for importance sampling
float BVHNode::pdf_value(const Vec3& o, const Vec3& v) const {
    return 0.5f * left->pdf_value(o, v) + 0.5f * right->pdf_value(o, v);
}

// Generate a random direction for importance sampling
Vec3 BVHNode::random(const Vec3& o, Xoshiro128PlusPlus& rng) const {
    if (rng.rand_float() < 0.5f) return left->random(o, rng);
    return right->random(o, rng);
}