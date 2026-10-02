#include "KingSystem/Utils/MathUtil.h"

namespace ksys::util {

float sub_71011EF0CC(float angle) {
    return angle - int((angle + (angle > sead::Mathf::pi() ? sead::Mathf::pi() : -sead::Mathf::pi())) /
                       (2 * sead::Mathf::pi())) *
                       (2 * sead::Mathf::pi());
}

void sub_71011EEB08(sead::Vector3f* axis, f32* angle, const sead::Vector3f& from,
                    const sead::Vector3f& to, const sead::Vector3f& default_axis) {
    axis->setCross(from, to);
    if (axis->x == 0.0f && axis->y == 0.0f && axis->z == 0.0f) {
        *axis = default_axis;
        *angle = from.dot(to) < 0.0f ? sead::Mathf::pi() : 0.0f;
        return;
    }
    const f32 len = axis->normalize();
    *angle = sead::Mathf::abs(sub_71011EF0CC(std::atan2(len, from.dot(to))));
}

void sub_71011EFA00(sead::Vector3f* out, const sead::Vector3f& v, const sead::Vector3f& n) {
    *out = -(n * v.dot(n) - v);
}

void sub_71011EFA54(sead::Vector3f* out, const sead::Vector3f& v, const sead::Vector3f& n) {
    const f32 d = v.dot(n);
    *out = n;
    *out *= d;
}

void sub_71011F00EC(sead::Matrix34f* mtx, const sead::Vector3f& front, const sead::Vector3f& up,
                    const sead::Vector3f& pos, bool) {
    sead::Vector3f side;
    side.setCross(up, front);
    side.normalize();
    sead::Vector3f dir;
    dir.setCross(side, up);
    dir.normalize();
    mtx->setBase(0, side);
    mtx->setBase(1, up);
    mtx->setBase(2, dir);
    mtx->setBase(3, pos);
}

}  // namespace ksys::util
