#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <arm_neon.h>

// NEON-accelerated Vec3
struct alignas(16) Vec3 {
    float x, y, z, w = 0.0;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

    Vec3 operator+(const Vec3& b) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t bb = vld1q_f32(&b.x);
        float32x4_t res = vaddq_f32(a, bb);
        Vec3 out;
        vst1q_f32(&out.x, res);
        return out;
    }

    Vec3 operator-(const Vec3& b) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t bb = vld1q_f32(&b.x);
        float32x4_t res = vsubq_f32(a, bb);
        Vec3 out;
        vst1q_f32(&out.x, res);
        return out;
    }

    Vec3 operator*(float b) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t scalar = vdupq_n_f32(b);
        float32x4_t res = vmulq_f32(a, scalar);
        Vec3 out;
        vst1q_f32(&out.x, res);
        return out;
    }

    Vec3 operator/(float b) const {
        return *this * (1.0f / b);
    }

    Vec3 mul(const Vec3& b) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t bb = vld1q_f32(&b.x);
        float32x4_t res = vmulq_f32(a, bb);
        Vec3 out;
        vst1q_f32(&out.x, res);
        return out;
    }

    Vec3 norm() const {
        float len = length();
        return len > 0 ? *this / len : *this;
    }

    float dot(const Vec3& b) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t bb = vld1q_f32(&b.x);
        float32x4_t mul = vmulq_f32(a, bb);
        float32x2_t sum = vadd_f32(vget_low_f32(mul), vget_high_f32(mul));
        return vget_lane_f32(vpadd_f32(sum, sum), 0);
    }

    Vec3 cross(const Vec3& b) const {
        return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }

    float length() const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t mul = vmulq_f32(a, a);
        float32x2_t sum = vadd_f32(vget_low_f32(mul), vget_high_f32(mul));
        sum = vpadd_f32(sum, sum);
        return std::sqrt(vget_lane_f32(sum, 0));
    }

    Vec3 clamp(float min_val, float max_val) const {
        float32x4_t a = vld1q_f32(&x);
        float32x4_t minv = vdupq_n_f32(min_val);
        float32x4_t maxv = vdupq_n_f32(max_val);
        float32x4_t res = vmaxq_f32(minv, vminq_f32(a, maxv));
        Vec3 out;
        vst1q_f32(&out.x, res);
        return out;
    }
};

#endif // VEC3_H