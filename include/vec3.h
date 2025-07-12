#ifndef VEC3_H
#define VEC3_H

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

};

#endif // VEC3_H