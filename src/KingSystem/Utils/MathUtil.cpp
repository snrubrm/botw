#include "KingSystem/Utils/MathUtil.h"
#include <cstdlib>
#include <math/seadQuat.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::util {

s64 sub_71011EE4C0(s64 difference) {
    const s64 magnitude = std::abs(difference);
    return magnitude > 0x80000000LL ? 0x100000000LL - magnitude : magnitude;
}

// NON_MATCHING: sUnk_7101EC6BA0 is defined in this file, so the angleDiff mask folds away (the original loads it
// through the GOT); branch layout follows from that.
bool sub_71011EE4EC(Unk_7101EC6BAC* angle, u32 target, u32 step) {
    const u32 current = angle->value;
    if (current == target)
        return true;

    const s64 delta = s32(angleDiff(target, *angle).value) < 0 ? -s64(step) : s64(step);
    const u32 next = current + u32(delta);
    bool reached;
    if (delta > 0) {
        if (current < next)
            reached = current <= target && target <= next;
        else
            reached = current <= target || target <= next;
    } else if (delta < 0) {
        if (next < current)
            reached = target <= current && next <= target;
        else
            reached = target <= current || next <= target;
    } else {
        return current == next;
    }

    if (reached) {
        angle->value = target;
        return true;
    }
    angle->value = next;
    return false;
}

// NON_MATCHING: sub_71011EE4B8 is defined in this unit, so its calls are inlined and the
// sUnk_7101EC6BA0 mask folds to -1 here; the original keeps four out-of-line calls and a GOT load of the
// mask (the same same-unit constants problem as sub_71011EE4EC).
bool sub_71011EE5A8(Unk_7101EC6BAC* angle, u32 target, s32 max_step, s32 snap_step, f32 ratio) {
    const s32 remaining = sub_71011EE4B8(angleDiff(target, *angle));
    if (remaining == 0)
        return true;

    if (ratio <= 0.0f)
        ratio = 1.0f;
    const s32 delta = s32(ratio * static_cast<f32>(remaining));

    const s32 snap = snap_step > 0 ? snap_step : 0;
    if (delta <= snap && -snap <= delta) {
        if (remaining < 0) {
            angle->value -= u32(snap);
            if (sub_71011EE4B8(angleDiff(target, *angle)) < 0)
                return false;
        } else {
            angle->value += u32(snap);
            if (sub_71011EE4B8(angleDiff(target, *angle)) > 0)
                return false;
        }
        angle->value = target;
        return true;
    }

    const s32 step = max_step > 0 ? max_step : 0;
    if (delta > step) {
        angle->value += u32(step);
    } else if (delta >= -step) {
        angle->value += u32(delta);
        return angle->value == target;
    } else {
        angle->value -= u32(step);
    }
    return false;
}

bool sub_71011EE6FC(sead::Vector3f* a, sead::Vector3f* b, f32 ratio) {
    return sub_71011EE70C(a, b, ratio, sead::Mathf::pi2(), 0.0f);
}

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

bool sub_71011EECAC(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to,
                    f32 max_angle) {
    sead::Vector3f axis;
    f32 angle;
    sub_71011EEB08(&axis, &angle, from, to, sead::Vector3f::ey);
    if (angle <= max_angle) {
        *out = to;
        return true;
    }
    sead::Quatf quaternion;
    quaternion.setAxisRadian(axis, max_angle);
    sead::Matrix33f mtx;
    mtx.fromQuat(quaternion);
    *out = from;
    out->mul(mtx);
    return false;
}

void sub_71011EF168(sead::Vector3f* out, const sead::Matrix33f& from,
                    const sead::Matrix33f& to, const sead::Vector3f& default_axis) {
    f32 angle;
    sub_71011EF1C4(out, &angle, from, to, default_axis);
    *out *= angle;
}

// NON_MATCHING: the in-place setInverse/setMul chain and the negate stores are scheduled differently
// (register allocation in the 3x3 multiply, one extra store); the operations match.
void sub_71011EF1C4(sead::Vector3f* axis, f32* angle, const sead::Matrix33f& from,
                    const sead::Matrix33f& to, const sead::Vector3f& default_axis) {
    sead::Matrix33f mtx;
    mtx.setInverse(from);
    mtx.setMul(mtx, to);

    sead::Quatf quat;
    mtx.toQuat(quat);
    quat.normalize();

    axis->set(quat.x, quat.y, quat.z);
    axis->normalize();
    if (quat.w < 0.0f)
        axis->set(-axis->x, -axis->y, -axis->z);

    const f32 length = axis->normalize();
    if (length > 0.001f) {
        *angle = 2.0f * std::acos(std::min(sead::Mathf::abs(quat.w), 1.0f));
    } else {
        *axis = default_axis;
        *angle = 0.0f;
    }
}

void sub_71011EF4C0(sead::Vector3f* out, const sead::Matrix34f& from,
                    const sead::Matrix34f& to, const sead::Vector3f& default_axis) {
    f32 angle;
    sub_71011EF51C(out, &angle, from, to, default_axis);
    *out *= angle;
}

// NON_MATCHING: the negate at the w < 0 sign flip stores z before x/y here (register colouring only);
// all other instructions match.
void sub_71011EF51C(sead::Vector3f* axis, f32* angle, const sead::Matrix34f& from,
                    const sead::Matrix34f& to, const sead::Vector3f& default_axis) {
    sead::Matrix34f mtx;
    mtx.setInverse(from);
    mtx.setMul(mtx, to);

    sead::Quatf quat;
    mtx.toQuat(quat);
    quat.normalize();

    axis->set(quat.x, quat.y, quat.z);
    axis->normalize();
    if (quat.w < 0.0f)
        axis->set(-axis->x, -axis->y, -axis->z);

    const f32 length = axis->normalize();
    if (length > 0.001f) {
        *angle = 2.0f * std::acos(std::min(sead::Mathf::abs(quat.w), 1.0f));
    } else {
        *axis = default_axis;
        *angle = 0.0f;
    }
}

// NON_MATCHING: same as sub_71011EF51C, the sign-flip store order differs (register colouring only).
void sub_71011EF78C(sead::Vector3f* axis, f32* angle, const sead::Matrix34f& from,
                    const sead::Matrix34f& to, const sead::Vector3f& default_axis) {
    sead::Matrix34f mtx;
    mtx.setInverse(from);
    mtx.setMul(to, mtx);

    sead::Quatf quat;
    mtx.toQuat(quat);
    quat.normalize();

    axis->set(quat.x, quat.y, quat.z);
    axis->normalize();
    if (quat.w < 0.0f)
        axis->set(-axis->x, -axis->y, -axis->z);

    const f32 length = axis->normalize();
    if (length > 0.001f) {
        *angle = 2.0f * std::acos(std::min(sead::Mathf::abs(quat.w), 1.0f));
    } else {
        *axis = default_axis;
        *angle = 0.0f;
    }
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
                    const sead::Vector3f& pos, bool unused) {
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

// NON_MATCHING: the translation clamp and the rotation block agree operation for operation; the
// residue is register allocation in the 4x4 multiply and the stack slots of the axis/angle/rotation
// temporaries (our frame is 0x10 smaller).
bool sub_71011F03C8(sead::Matrix34f* out, const sead::Matrix34f& from, const sead::Matrix34f& to,
                    f32 t, f32 max_angle, f32 min_angle, f32 max_step, f32 min_step) {
    const sead::Vector3f from_pos = from.getTranslation();
    sead::Vector3f translation = from_pos;
    const sead::Vector3f diff = to.getTranslation() - from_pos;
    if (diff.length() > min_step) {
        f32 step = t;
        if (diff.length() * t > max_step)
            step = max_step / diff.length();
        else if (diff.length() * t < min_step)
            step = min_step / diff.length();
        translation = from_pos + diff * step;
    } else {
        translation = to.getTranslation();
    }

    sead::Vector3f axis = sead::Vector3f::zero;
    f32 angle;
    sub_71011EF51C(&axis, &angle, from, to, sead::Vector3f::ey);
    axis *= angle;
    const f32 length = axis.normalize();
    if (length < min_angle) {
        *out = to;
        return true;
    }

    const f32 radian = sead::Mathf::clamp(sead::Mathf::abs(length * t), min_angle, max_angle);
    sead::Quatf quaternion;
    quaternion.setAxisRadian(axis, sead::Mathf::sign(length) * radian);
    sead::Matrix34f rotation;
    rotation.fromQuat(quaternion);
    out->setMul(from, rotation);
    out->setTranslation(translation);
    return false;
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

void sub_71011EFB40(sead::Vector3f* vec, const sead::Vector3f& rotation) {
    sead::Vector3f axis = rotation;
    const f32 angle = axis.normalize();
    if (angle > 0.001f) {
        sead::Quatf quaternion;
        quaternion.setAxisRadian(axis, angle);
        sead::Matrix33f rotation_matrix;
        rotation_matrix.fromQuat(quaternion);
        vec->setMul(rotation_matrix, *vec);
    }
}

void sub_71011EFCA8(sead::Matrix34f* matrix, const sead::Vector3f& rotation) {
    sead::Vector3f axis = rotation;
    const f32 angle = axis.normalize();
    if (angle > 0.001f) {
        sead::Quatf quaternion;
        quaternion.setAxisRadian(axis, angle);
        sead::Matrix34f rotation_matrix;
        rotation_matrix.fromQuat(quaternion);
        matrix->setMul(*matrix, rotation_matrix);
    }
}

void sub_71011EFE58(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up, bool unused) {
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

void sub_71011EFFA8(sead::Matrix33f* mtx, const sead::Vector3f& front, const sead::Vector3f& up, bool unused) {
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

namespace ksys::util {

// .rodata 0x7101ec6ba0-0x7101ec6baf, between constants of the TUs around 0x71011e5240 and
// 0x71011fc108 (that they belong to this TU is a guess).
const u32 sUnk_7101EC6BA0 = 0xffffffff;
const f32 sUnk_7101EC6BA4 = 360.0f / 4294967296.0f;
const f32 sUnk_7101EC6BA8 = 2 * sead::numbers::pi / 4294967296.0f;
const Unk_7101EC6BAC sUnk_7101EC6BAC{0};

s32 sub_71011EE4B8(Unk_7101EC6BAC angle) {
    return angle.value;
}

}  // namespace ksys::util

Unk_71025138e8::~Unk_71025138e8() = default;
