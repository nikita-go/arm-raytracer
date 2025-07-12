#ifndef AABB_H
#define AABB_H

#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/constants.h"
#include <algorithm>

// Axis-Aligned Bounding Box with NEON-accelerated operations
struct alignas(64) AABB {
    Vec3 min, max;

    // Initializes to given bounds or an inverted box by default
    AABB(const Vec3& mi = Vec3(INF, INF, INF), const Vec3& ma = Vec3(-INF, -INF, -INF))
        : min(mi), max(ma) {}

    // Returns a new AABB that encompasses this and another box
    AABB merge(const AABB& b) const {
        float32x4_t min_a = vld1q_f32(&min.x);
        float32x4_t min_b = vld1q_f32(&b.min.x);
        float32x4_t max_a = vld1q_f32(&max.x);
        float32x4_t max_b = vld1q_f32(&b.max.x);

        Vec3 new_min, new_max;
        vst1q_f32(&new_min.x, vminq_f32(min_a, min_b));
        vst1q_f32(&new_max.x, vmaxq_f32(max_a, max_b));

        return AABB(new_min, new_max);
    }

    // Ray-box intersection using slabs method and NEON vectors
    bool intersect(const Ray& r, float& tmin_out, float& tmax_out) const {
        float32x4_t omin = vld1q_f32(&min.x);
        float32x4_t omax = vld1q_f32(&max.x);
        float32x4_t ro = vld1q_f32(&r.o.x);
        float32x4_t rd = vld1q_f32(&r.d.x);
        float32x4_t inv_d = vdivq_f32(vdupq_n_f32(1.0f), rd);

        float32x4_t t1 = vmulq_f32(vsubq_f32(omin, ro), inv_d);
        float32x4_t t2 = vmulq_f32(vsubq_f32(omax, ro), inv_d);

        float32x4_t tmin_vec = vminq_f32(t1, t2);
        float32x4_t tmax_vec = vmaxq_f32(t1, t2);

        float tmin = std::max({vgetq_lane_f32(tmin_vec,0), vgetq_lane_f32(tmin_vec,1), vgetq_lane_f32(tmin_vec,2)});
        float tmax = std::min({vgetq_lane_f32(tmax_vec,0), vgetq_lane_f32(tmax_vec,1), vgetq_lane_f32(tmax_vec,2)});

        tmin = std::max(0.f, tmin);
        tmax = std::min(INF, tmax);

        tmin_out = tmin;
        tmax_out = tmax;
        return tmax >= tmin && tmax > 0;
    }
};

#endif // AABB_H