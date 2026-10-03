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
// 0x71011eeb08: the rotation (unit axis, angle in [0, pi]) from `from` to `to`; `default_axis` is used
// when they are parallel.
void sub_71011EEB08(sead::Vector3f* axis, float* angle, const sead::Vector3f& from,
                    const sead::Vector3f& to, const sead::Vector3f& default_axis);

// 0x71011efa00: the part of `vec` perpendicular to `axis` (unit vector): vec - axis * dot(vec, axis).
void sub_71011EFA00(sead::Vector3f* out, const sead::Vector3f& vec, const sead::Vector3f& axis);

// 0x71011efa54: the projection of `vec` on `axis` (unit vector): axis * dot(vec, axis).
void sub_71011EFA54(sead::Vector3f* out, const sead::Vector3f& vec, const sead::Vector3f& axis);

// 0x71011efaa4: |dot(a, b)|.
float sub_71011EFAA4(const sead::Vector3f& a, const sead::Vector3f& b);

// 0x71011efad8: length of the part of `vec` perpendicular to `axis`.
float sub_71011EFAD8(const sead::Vector3f& vec, const sead::Vector3f& axis);


// 0x71011f0260: builds a matrix whose Z axis is `front` and Y axis is `up` made perpendicular to it.
void sub_71011F0260(sead::Matrix34f* mtx, const sead::Vector3f& front, const sead::Vector3f& up,
                    const sead::Vector3f& pos);

// 0x71011f0f88 / 0x71011f0fc8 / 0x71011f1040 / 0x71011f10f4: whether any component is NaN or infinite.
bool sub_71011F0F88(const float& value);
bool sub_71011F0FC8(const sead::Vector2f& vec);
bool sub_71011F1040(const sead::Vector3f& vec);

bool sub_71011F10F4(const sead::Matrix34f& mtx);

// 0x71011efe58 / 0x71011effa8: Matrix33 versions of sub_71011F00EC / sub_71011F0260.
void sub_71011EFE58(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up);
void sub_71011EFFA8(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up);

// 0x71011eee2c / 0x71011eee98: sets x/z of `vec` to the XZ direction of `angle` (sead index /
// radians) scaled by `length`; 0x71011eeee0 / 0x71011eef5c add it instead.
void sub_71011EEE2C(sead::Vector3f* vec, const u32& angle, float length);
void sub_71011EEE98(sead::Vector3f* vec, float angle, float length);
void sub_71011EEEE0(sead::Vector3f* vec, const u32& angle, float length);
void sub_71011EEF5C(sead::Vector3f* vec, float angle, float length);

// 0x71011eefb4 / 0x71011ef070: rotate `vec` around the X / Z axis by `angle` (radians).
void sub_71011EEFB4(sead::Vector3f* vec, float angle);
void sub_71011EF070(sead::Vector3f* vec, float angle);

// 0x71011ef10c: sub_71011EEB08 as a single rotation vector (axis * angle).
void sub_71011EF10C(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to,
                    const sead::Vector3f& default_axis);

// Placeholder (no name known; named after its zero constant): a 4-byte angle index in
// sead::Mathf *Idx units (2^32 = one turn). It is returned through x8 (Player::x_5,
// 0x710092dba4), so it is not trivially copyable in the original. Constants (const objects with
// external linkage in .rodata, read through the GOT; ~50 users each): sUnk_7101EC6BA0 (0xffffffff),
// sUnk_7101EC6BA4 (360 / 2^32, index to degrees), sUnk_7101EC6BA8 (2pi / 2^32, index to radians),
// sUnk_7101EC6BAC (zero angle).
struct Unk_7101EC6BAC {
    explicit constexpr Unk_7101EC6BAC(u32 v) : value(v) {}
    Unk_7101EC6BAC(const Unk_7101EC6BAC& other) : value(other.value) {}
    u32 value;
};

// 0x71011ee4b8 (declaration only): the signed value of an angle index (inline in the original, emitted
// out of line).
s32 sub_71011EE4B8(Unk_7101EC6BAC angle);

extern const u32 sUnk_7101EC6BA0;
extern const f32 sUnk_7101EC6BA4;
extern const f32 sUnk_7101EC6BA8;
extern const Unk_7101EC6BAC sUnk_7101EC6BAC;

}  // namespace ksys::util
