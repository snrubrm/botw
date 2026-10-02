#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
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

// 0x7100737708-0x710073771c: forwarders to the ksys::act per-frame velocity setters
// (actActorUtil.h, 0x7100ee60a0-0x7100ee62b0). Defined in aiUnk_71007377D4.cpp.
void sub_7100737708(ksys::phys::CharacterController* controller, f32 value);
void sub_710073770C(ksys::phys::CharacterController* controller, f32 value, const sead::Vector3f& up);
void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel);
void sub_7100737714(ksys::phys::CharacterController* controller, const sead::Vector3f& ang_vel);
void sub_7100737718(ksys::phys::RigidBody* body, const sead::Vector3f& vel);
void sub_710073771C(ksys::phys::RigidBody* body, const sead::Vector3f& ang_vel);

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
/// 0x7100738c88: links the physics of `actor` to `other`'s (ActorPhysics::x_5), if both have one.
void sub_7100738C88(ksys::act::Actor* actor, ksys::act::Actor* other);

// Single-branch functions of the same area forwarding to KingSystem actor utilities (0x7100ee5b84,
// 0x7100ee60ac). Names are placeholders.

/// Gravity acting on the actor (character controller gravity, or world gravity scaled by the main
/// rigid body's gravity factor).
void sub_710072DC50(sead::Vector3f* gravity, ksys::act::Actor* actor);
void sub_710072C1B4(ksys::phys::CharacterController* controller, const sead::Vector3f& up);

/// 0x710072fec4 (declared only): probes along `dir` from the actor (used by the cliff/edge checks of
/// several enemy AIs); optionally outputs a position and a flag. Placeholder name; the position of
/// the f32 argument among the integer arguments is unknown.
bool sub_710072FEC4(ksys::act::Actor* actor, const sead::Vector3f& dir, f32 distance,
                    sead::Vector3f* out_pos, bool flag, bool* out_flag);

/// 0x710072f28c (declared only): line reachability check from `from` (NaN: the actor's position) to
/// `to` on the navmesh / collision; optional outputs. Placeholder name; parameter types partly
/// guessed (a5 is stored as a byte and a word; the three floats are tolerances, -1 = default).
bool sub_710072F28C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_normal, sead::Vector3f* out_pos, s32 a5, bool a6, f32 a7,
                    f32 a8, f32 a9);
/// 0x710072e154: sub_710072F28C from the actor's position to `target` with default tolerances.
bool sub_710072E154(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    s32 a4);
/// 0x710072ec90: HavokAI navmesh query from `pos` to `target` (HavokAI::sub_7100F86174);
/// `out` receives the resulting point (or `pos`). True if the query hit, or if the point is within
/// `max_dist` of `target` in XZ and less than `max_height` apart in Y.
bool sub_710072EC90(const sead::Vector3f& pos, const sead::Vector3f& target, sead::Vector3f* out,
                    f32 max_dist, f32 max_height);

/// 0x710072e1b4: whether the actor is an enemy whose target state (sub_71005D9744) is 2 or 5, or 3
/// when `include_3` is set. Placeholder name.
bool sub_710072E1B4(ksys::act::Actor* actor, bool include_3);
// 0x710072e280 (CSV name): casts a world ray from `pos` to `pos + dir * distance` (the TU after
// uking::Unk_71024739d0, sub_710090DB04); writes the hit position.
bool somePositionCalc(sead::Vector3f* hit_position, const sead::Vector3f& pos,
                      const sead::Vector3f& dir, f32 distance);

/// 0x710072ddb8: whether the direction from the translation of `mtx` to `target` is within `angle`
/// (radians) of the matrix's forward axis, both projected onto the XZ plane. Placeholder name.
bool sub_710072DDB8(const sead::Vector3f& target, const sead::Matrix34f& mtx, f32 angle);

/// 0x710072e928: world ray cast (RayCastBodyQuery, GroundHit 0xf, contact layer type 0) from `from` to
/// `to`, both raised by `y_offset`. On a hit, writes the hit position / normal and (for `hit_info`)
/// a u32 of the query at +0x8 and nullptr at +0x10 when the pointers are non-null. Placeholder name;
/// the type of `hit_info` is unknown.
bool sub_710072E928(const sead::Vector3f& from, const sead::Vector3f& to, sead::Vector3f* hit_pos,
                    sead::Vector3f* hit_normal, void* hit_info, f32 y_offset);
