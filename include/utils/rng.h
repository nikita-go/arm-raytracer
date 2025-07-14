#ifndef RNG_H
#define RNG_H

#include <cstdint>
#include <vector>

// Rotate x to the left by k bits
inline uint32_t rotl(const uint32_t x, int k) {
    return (x << k) | (x >> (32 - k));
}

// Fast RNG (xoshiro128++)
struct Xoshiro128PlusPlus {
    uint32_t s[4];
    std::vector<float> random_batch;
    size_t batch_pos;

    Xoshiro128PlusPlus(uint32_t seed) : batch_pos(0) {
        // Properly initialize using splitmix32 to spread bits
        uint32_t z = seed;
        for (int i = 0; i < 4; i++) {
            z += 0x9e3779b9;
            uint32_t t = z;
            t = (t ^ (t >> 15)) * 0x85ebca6b;
            t = (t ^ (t >> 13)) * 0xc2b2ae35;
            s[i] = t ^ (t >> 16);
        }
        generate_batch(1024); // Precompute 1024 random numbers
    }

    uint32_t next() {
        const uint32_t result = rotl(s[0] + s[3], 7) + s[0];
        const uint32_t t = s[1] << 9;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 11);
        return result;
    }

    void generate_batch(size_t size) {
        random_batch.resize(size);
        for (size_t i = 0; i < size; i++) {
            random_batch[i] = (next() >> 8) * (1.0f / (1 << 24));
        }
        batch_pos = 0;
    }

    float rand_float() {
        if (batch_pos >= random_batch.size()) generate_batch(random_batch.size());
        return random_batch[batch_pos++];
    }
};

#endif // RNG_H