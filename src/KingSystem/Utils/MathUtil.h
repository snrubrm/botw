#pragma once

#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace ksys::util {

/// Remap `value` from a [low, high] range to [new_low, new_high].
inline float remapRange(float value, float low, float high, float new_low, float new_high) {
    return new_low + (value - low) * (new_high - new_low) / (high - low);
}

/// Clamp `value` to [low, high] and then remap the value to the range [new_low, new_high].
inline float clampAndRemapRange(float value, float low, float high, float new_low, float new_high) {
    value = sead::Mathf::clamp(value, low, high);
    return remapRange(value, low, high, new_low, new_high);
}

// too specific for sead
inline float sqXZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    return sead::Mathf::square(a.x - b.x) + sead::Mathf::square(a.z - b.z);
}

inline float dot(sead::Vector3f u, const sead::Matrix34f& mtx, int row) {
    return u.x * mtx(row, 0) + u.y * mtx(row, 1) + u.z * mtx(row, 2);
}

inline void lerp(sead::Vector3f* result, const sead::Vector3f& a, const sead::Vector3f& b,
                 float t) {
    result->x = a.x + (b.x - a.x) * t;
    result->y = a.y + (b.y - a.y) * t;
    result->z = a.z + (b.z - a.z) * t;
}

inline sead::Vector3f lerp(const sead::Vector3f& a, const sead::Vector3f& b, float t) {
    sead::Vector3f result;
    lerp(&result, a, b, t);
    return result;
}

inline bool isVectorInvalid(const sead::Vector3f& vec) {
    for (int i = 0; i < 3; ++i) {
        if (std::isnan(vec.e[i]))
            return true;
    }
    return false;
}

inline bool isMatrixInvalid(const sead::Matrix34f& matrix) {
    for (float x : matrix.a) {
        if (std::isnan(x))
            return true;
    }
    return false;
}

inline sead::Vector3f getCol(const sead::Matrix34f& mtx, int col) {
    sead::Vector3f result;
    mtx.getBase(result, col);
    return result;
}

// 0x71011ef010: rotates `vec` around the Y axis by `angle` (radians).
void sub_71011EF010(sead::Vector3f* vec, float angle);

// 0x71011ef0cc: wraps `angle` (radians) into [-pi, pi].
float sub_71011EF0CC(float angle);

// 0x71011eeb08: rotation `axis` (normalised `from` x `to`, or `default_axis` if they are parallel) and
// unsigned `angle` that rotate `from` onto `to`.
void sub_71011EEB08(sead::Vector3f* axis, f32* angle, const sead::Vector3f& from,
                    const sead::Vector3f& to, const sead::Vector3f& default_axis);

// 0x71011efa00: `out` = `v` minus its projection onto `n` (`n` is assumed to be normalised).
void sub_71011EFA00(sead::Vector3f* out, const sead::Vector3f& v, const sead::Vector3f& n);

// 0x71011efa54: `out` = projection of `v` onto `n` (`n` is assumed to be normalised).
void sub_71011EFA54(sead::Vector3f* out, const sead::Vector3f& v, const sead::Vector3f& n);

// 0x71011f00ec: builds `mtx` from an up vector and an approximate front vector (orthonormalised),
// translated to `pos`. The last parameter is unused.
void sub_71011F00EC(sead::Matrix34f* mtx, const sead::Vector3f& front, const sead::Vector3f& up,
                    const sead::Vector3f& pos, bool);

// 0x71011f03c8: moves `from` towards `to` (by the ratio `t`, with limits a5 - a8) and stores the
// result in `out`.
bool sub_71011F03C8(sead::Matrix34f* out, const sead::Matrix34f& from, const sead::Matrix34f& to,
                    f32 t, f32 a5, f32 a6, f32 a7, f32 a8);

}  // namespace ksys::util
