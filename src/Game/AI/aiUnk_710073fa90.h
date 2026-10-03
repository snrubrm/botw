#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
class BoneHandle;
}

namespace ksys::phys {
class CharacterController;
class RigidBody;
}  // namespace ksys::phys

// Unnamed helpers that operate on a rotation matrix (sead::Matrix33f) embedded in many AI actions.
// They live in two parallel groups of functions (0x710073f7f0-0x7100741034 and 0x7100741034-0x7100741c24)
// with identical interfaces; the second group passes `true` to the shared basis builders (0x71011efe58,
// 0x71011effa8). Names are placeholders (address of the function).

// --- Group A ---

// Copies the rotation part of the actor's transform (character controller, else main rigid body,
// else Actor::getMtx()) into `mtx`. 0x710073FA90 only forwards to 0x710073FA94.
void sub_710073FA90(sead::Matrix33f* mtx, const ksys::act::Actor* actor);
void sub_710073FA94(sead::Matrix33f* mtx, const ksys::act::Actor* actor);
// Copies the rotation part of `transform` into `mtx`.
void sub_710073FB74(sead::Matrix33f* mtx, const sead::Matrix34f& transform);
// Rotates `mtx` towards `target` (or the rotation built from the given vectors); returns whether the
// target was reached.
bool sub_710073FBC0(sead::Matrix33f* mtx, const sead::Matrix33f& target, f32 a, f32 b, f32 c);
bool sub_710073FF90(sead::Matrix33f* mtx, const sead::Matrix34f& target, f32 a, f32 b, f32 c);
bool sub_710074006C(sead::Matrix33f* mtx, const sead::Vector3f& v1, const sead::Vector3f& v2, bool flag,
                    f32 a, f32 b, f32 c);
bool sub_7100740118(sead::Matrix33f* mtx, const sead::Vector3f& v, f32 a, f32 b, f32 c);
bool sub_710074018C(sead::Matrix33f* mtx, const sead::Vector3f& v, f32 a, f32 b, f32 c);
bool sub_7100740200(sead::Matrix33f* mtx, const sead::Vector3f& v, f32 a, f32 b, f32 c);
bool sub_71007404F0(sead::Matrix33f* mtx, const sead::Matrix33f& target, f32 a);
bool sub_71007407F0(sead::Matrix33f* mtx, const sead::Vector3f& v1, const sead::Vector3f& v2, bool flag,
                    f32 a);
// Applies `mtx` (with a zero translation) to the character controller / rigid body / actor.
void sub_7100740E04(const sead::Matrix33f& mtx, ksys::phys::CharacterController* controller);
void sub_7100740E8C(const sead::Matrix33f& mtx, ksys::phys::RigidBody* body);
void sub_7100740F1C(const sead::Matrix33f& mtx, ksys::act::Actor* actor);

// 0x71007448c0 (declaration only): moves the transform of the bone handle `handle` towards `target` by
// `ratio` (BoneHandle::_68 / _98 blend). Placeholder name.
void sub_71007448C0(ksys::act::BoneHandle* handle, const sead::Matrix34f& target, f32 ratio);
// 0x7100744a54 (declaration only): the same with a target translation (Ragdoll::sub_7100226B04); the
// two last floats are ratios of the blend. Placeholder name.
void sub_7100744A54(ksys::act::BoneHandle* handle, const sead::Vector3f& target, f32 ratio, f32 a,
                    f32 b);

// --- Group B ---

void sub_7100741034(sead::Matrix33f* mtx, const ksys::act::Actor* actor);
void sub_7100741038(sead::Matrix33f* mtx, const ksys::act::Actor* actor);
void sub_7100741118(sead::Matrix33f* mtx, const sead::Matrix34f& transform);
bool sub_710074149C(sead::Matrix33f* mtx, const sead::Matrix34f& target, f32 a, f32 b, f32 c);
// 0x7100741628 (declaration only): rotates `mtx` towards the up direction `up` (the three floats are
// ratios / speeds); returns whether the target was reached.
bool sub_7100741628(sead::Matrix33f* mtx, const sead::Vector3f& up, f32 a, f32 b, f32 c);
bool sub_7100741578(sead::Matrix33f* mtx, const sead::Vector3f& v1, const sead::Vector3f& v2, bool flag,
                    f32 a, f32 b, f32 c);
bool sub_710074191C(sead::Matrix33f* mtx, const sead::Vector3f& v1, const sead::Vector3f& v2, bool flag,
                    f32 a);
// Rebuilds `mtx` from its z axis and `up`.
void sub_71007419B4(sead::Matrix33f* mtx, const sead::Vector3f& up);
void sub_71007419F4(const sead::Matrix33f& mtx, ksys::phys::CharacterController* controller);
void sub_7100741A7C(const sead::Matrix33f& mtx, ksys::phys::RigidBody* body);
void sub_7100741B0C(const sead::Matrix33f& mtx, ksys::act::Actor* actor);
