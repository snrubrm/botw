#include "KingSystem/Utils/MathUtil.h"

namespace ksys::util {

void sub_71011EF010(sead::Vector3f* vec, float angle) {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float x = vec->x;
    const float z = vec->z;
    vec->x = c * x + s * z;
    vec->z = -s * x + c * z;
}

float sub_71011EF0CC(float angle) {
    const float offset = angle > sead::Mathf::pi() ? sead::Mathf::pi() : -sead::Mathf::pi();
    return angle - static_cast<int>((angle + offset) / sead::Mathf::pi2()) * sead::Mathf::pi2();
}

void sub_71011EEB08(sead::Vector3f* axis, float* angle, const sead::Vector3f& from,
                    const sead::Vector3f& to, const sead::Vector3f& default_axis) {
    axis->setCross(from, to);
    if (axis->x == 0.0f && axis->y == 0.0f && axis->z == 0.0f) {
        *axis = default_axis;
        *angle = from.dot(to) < 0.0f ? sead::Mathf::pi() : 0.0f;
        return;
    }
    const float sin = axis->normalize();
    *angle = sead::Mathf::abs(sub_71011EF0CC(std::atan2(sin, from.dot(to))));
}

void sub_71011EFA00(sead::Vector3f* out, const sead::Vector3f& vec, const sead::Vector3f& axis) {
    *out = -(axis * vec.dot(axis) - vec);
}

void sub_71011EFA54(sead::Vector3f* out, const sead::Vector3f& vec, const sead::Vector3f& axis) {
    const float d = vec.dot(axis);
    *out = axis;
    *out *= d;
}

float sub_71011EFAA4(const sead::Vector3f& a, const sead::Vector3f& b) {
    return sead::Mathf::abs(a.dot(b));
}

float sub_71011EFAD8(const sead::Vector3f& vec, const sead::Vector3f& axis) {
    return (axis * vec.dot(axis) - vec).length();
}

}  // namespace ksys::util

namespace ksys::util {

void sub_71011F00EC(sead::Matrix34f* mtx, const sead::Vector3f& front, const sead::Vector3f& up,
                    const sead::Vector3f& pos, bool) {
    sead::Vector3f x;
    x.setCross(up, front);
    x.normalize();
    sead::Vector3f z;
    z.setCross(x, up);
    z.normalize();
    mtx->setBase(0, x);
    mtx->setBase(1, up);
    mtx->setBase(2, z);
    mtx->setBase(3, pos);
}

void sub_71011F0260(sead::Matrix34f* mtx, const sead::Vector3f& front, const sead::Vector3f& up,
                    const sead::Vector3f& pos) {
    sead::Vector3f x;
    x.setCross(up, front);
    x.normalize();
    sead::Vector3f y;
    y.setCross(front, x);
    y.normalize();
    mtx->setBase(0, x);
    mtx->setBase(1, y);
    mtx->setBase(2, front);
    mtx->setBase(3, pos);
}

bool sub_71011F0F88(const float& value) {
    if (std::isnan(value))
        return true;
    return sead::Mathf::abs(value) > sead::Mathf::maxNumber();
}

bool sub_71011F0FC8(const sead::Vector2f& vec) {
    for (float x : vec.e) {
        if (std::isnan(x))
            return true;
    }
    return sead::Mathf::abs(vec.x) > sead::Mathf::maxNumber() ||
           sead::Mathf::abs(vec.y) > sead::Mathf::maxNumber();
}

bool sub_71011F1040(const sead::Vector3f& vec) {
    if (isVectorInvalid(vec))
        return true;
    return sead::Mathf::abs(vec.x) > sead::Mathf::maxNumber() ||
           sead::Mathf::abs(vec.y) > sead::Mathf::maxNumber() ||
           sead::Mathf::abs(vec.z) > sead::Mathf::maxNumber();
}

bool sub_71011F10F4(const sead::Matrix34f& mtx) {
    for (float x : mtx.a) {
        if (std::isnan(x))
            return true;
    }
    for (float x : mtx.a) {
        if (sead::Mathf::abs(x) > sead::Mathf::maxNumber())
            return true;
    }
    return false;
}

void sub_71011EFE58(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up) {
    sead::Vector3f x;
    x.setCross(up, front);
    x.normalize();
    sead::Vector3f z;
    z.setCross(x, up);
    z.normalize();
    mtx->setBase(0, x);
    mtx->setBase(1, up);
    mtx->setBase(2, z);
}

void sub_71011EFFA8(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up) {
    sead::Vector3f x;
    x.setCross(up, front);
    x.normalize();
    sead::Vector3f y;
    y.setCross(front, x);
    y.normalize();
    mtx->setBase(0, x);
    mtx->setBase(1, y);
    mtx->setBase(2, front);
}

void sub_71011EEE2C(sead::Vector3f* vec, const u32& angle, float length) {
    vec->x = sead::Mathf::sinIdx(angle) * length;
    vec->z = sead::Mathf::cosIdx(angle) * length;
}

void sub_71011EEE98(sead::Vector3f* vec, float angle, float length) {
    vec->x = std::sin(angle) * length;
    vec->z = std::cos(angle) * length;
}

void sub_71011EEEE0(sead::Vector3f* vec, const u32& angle, float length) {
    vec->x += sead::Mathf::sinIdx(angle) * length;
    vec->z += sead::Mathf::cosIdx(angle) * length;
}

void sub_71011EEF5C(sead::Vector3f* vec, float angle, float length) {
    vec->x += std::sin(angle) * length;
    vec->z += std::cos(angle) * length;
}

void sub_71011EEFB4(sead::Vector3f* vec, float angle) {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float y = vec->y;
    const float z = vec->z;
    vec->y = c * y - s * z;
    vec->z = s * y + c * z;
}

void sub_71011EF070(sead::Vector3f* vec, float angle) {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float x = vec->x;
    const float y = vec->y;
    vec->x = c * x - s * y;
    vec->y = s * x + c * y;
}

void sub_71011EF10C(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to,
                    const sead::Vector3f& default_axis) {
    float angle;
    sub_71011EEB08(out, &angle, from, to, default_axis);
    *out *= angle;
}

}  // namespace ksys::util
