#pragma once

#include <cmath>
#include <math/seadVector.h>

namespace ksys::phys {
class RigidBody;
}

namespace uking::act {

// Helper TU 0x71002c8640 - 0x71002c8fd4 used by the Motorcycle (and a few other physics-driven actors).
// The names are guesses from the code.

// 0x71002c8640 (CSV name): `out = b * dot(a, b)`, the part of `a` along `b`; returns the dot product.
f32 innerProductTimesA3(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b);
// 0x71002c8688: `out = a - b * dot(a, b)`, the part of `a` perpendicular to `b`; returns the dot product.
f32 perpendicularPart(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b);
// 0x71002c86dc: `parallel = b * dot(a, b); perpendicular = a - parallel`.
f32 splitParallelPerpendicular(sead::Vector3f* parallel, sead::Vector3f* perpendicular,
                               const sead::Vector3f& a, const sead::Vector3f& b);
// 0x71002c8774 / 0x71002c87e0: adds (x, y, z) to the linear / angular velocity of the body.
void addLinearVelocity(ksys::phys::RigidBody* body, f32 x, f32 y, f32 z);
void addAngularVelocity(ksys::phys::RigidBody* body, f32 x, f32 y, f32 z);
// 0x71002c884c: whether the body belongs to an actor with the tag IsTurnOffTouchMotorcycle.
bool isTurnOffTouchMotorcycle(ksys::phys::RigidBody* body);

// inline-only in the original (the sqrt / atan2 pair appears twice in a row in Motorcycle::x_35 and
// x_33); the name is a guess: the angle (in radians) between two vectors.
inline f32 angleBetweenVectors(const sead::Vector3f& a, const sead::Vector3f& b) {
    const f32 dot = a.dot(b);
    sead::Vector3f cross;
    cross.setCross(a, b);
    return std::atan2(cross.length(), dot);
}

}  // namespace uking::act
