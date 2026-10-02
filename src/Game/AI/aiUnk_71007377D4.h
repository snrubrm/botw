#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

namespace ksys::phys {
class CharacterController;
class RigidBody;
}  // namespace ksys::phys

// Velocity damping helpers of an unnamed AI utility translation unit (0x7100737000 - 0x7100738cb0).
// Each one exists for a CharacterController, a RigidBody and an Actor (which dispatches to its
// character controller or its main rigid body, Actor+0x190). The f32 argument is a ratio that makes
// the helper return early when it equals 1.0. Names are placeholders.

/// Reduces the linear velocity.
void sub_71007377D4(ksys::phys::CharacterController* controller, f32 ratio);
void sub_71007379FC(ksys::phys::RigidBody* body, f32 ratio);
void sub_7100738428(ksys::act::Actor* actor, f32 ratio);
/// Reduces the velocity along `dir`.
void sub_7100737C0C(ksys::phys::CharacterController* controller, f32 ratio,
                    const sead::Vector3f& dir);
void sub_7100738084(ksys::phys::RigidBody* body, f32 ratio, const sead::Vector3f& dir);
/// Velocity along `dir` (callers pass -Vector3f::ey; the original body uses -Vector3f::ey itself).
void sub_7100738488(ksys::act::Actor* actor, f32 ratio, const sead::Vector3f& dir);
void sub_710073852C(ksys::phys::CharacterController* controller, f32 ratio);
/// Reduces the angular velocity.
void sub_7100738660(ksys::phys::CharacterController* controller, f32 ratio);
void sub_7100738898(ksys::phys::RigidBody* body, f32 ratio);
void sub_7100738AA8(ksys::act::Actor* actor, f32 ratio);

// Single-branch functions of the same area forwarding to KingSystem actor utilities (0x7100ee5b84,
// 0x7100ee60ac). Names are placeholders.

/// Gravity acting on the actor (character controller gravity, or world gravity scaled by the main
/// rigid body's gravity factor).
void sub_710072DC50(sead::Vector3f* gravity, ksys::act::Actor* actor);
void sub_710072C1B4(ksys::phys::CharacterController* controller, const sead::Vector3f& up);
