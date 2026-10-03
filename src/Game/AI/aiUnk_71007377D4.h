#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physRayCast.h"

namespace ksys::act {
class Actor;
class BaseProcLink;
class Unk_7100d860d8;
}  // namespace ksys::act

namespace ksys::phys {
class CharacterController;
class MaterialMask;
class RigidBody;
class SystemGroupHandler;
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
// 0x7100738dc8 (declaration only): InstanceSet::sub_7100FBDFA4 with the actor's group handler.
void sub_7100738DC8(ksys::act::Actor* actor);
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
/// 0x7100738d28: same as sub_7100738C88 with the other system group handler (+0x190).
void sub_7100738D28(ksys::act::Actor* actor, ksys::act::Actor* other);

// Single-branch functions of the same area forwarding to KingSystem actor utilities (0x7100ee5b84,
// 0x7100ee60ac). Names are placeholders.

/// Gravity acting on the actor (character controller gravity, or world gravity scaled by the main
/// rigid body's gravity factor).
void sub_710072DC50(sead::Vector3f* gravity, ksys::act::Actor* actor);

/// inline-only in the original; name is a guess. Evidence: the same sequence (sub_710072DC50 into a
/// stack vector, returned by value) repeats in SmallDamageBackwardBase::calc_, KnockBackShock::enter_,
/// FlyMoveBase::enter_, TargetCircle::enter_, ... and the callers keep the result in the stack slot
/// of the gravity vector.
inline sead::Vector3f getGravity(ksys::act::Actor* actor) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    return gravity;
}

/// inline-only in the original; name is a guess. The up direction for a gravity vector: the normalized
/// negated vector (Y axis if it is null); the same sequence repeats in FlyMoveBase::enter_,
/// AnmDrivenSpeedBackWalk::calc_ (3x), RandomJump::calc_, TargetCircle::enter_, ...
inline sead::Vector3f getUpDir(const sead::Vector3f& gravity) {
    sead::Vector3f up = -gravity;
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    return up;
}

/// The actor's up direction.
inline sead::Vector3f getUpDir(ksys::act::Actor* actor) {
    return getUpDir(getGravity(actor));
}
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
/// 0x710072f788: sub_710072F28C from `from` to `to` with default tolerances; writes the position to
/// `out_pos`. Placeholder name.
bool sub_710072F788(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos);
/// 0x710072f7ac (lane2 s21): sub_710072F28C from `from` to `to` with the tolerance `a7` (a5 as in
/// sub_710072F28C). Placeholder name.
bool sub_710072F7AC(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a7);
/// 0x710072f7d0 (lane2 s21): sub_710072F28C from `from` to `to` with the actor's navmesh radius as the
/// first tolerance. Placeholder name.
bool sub_710072F7D0(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5);
/// 0x710072f854 (lane2 s21): like sub_710072F7D0 with `extra` added to the navmesh radius. Placeholder name.
bool sub_710072F854(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, f32 extra, s32 a5);
/// 0x710072f8e4 (lane2 s21): sub_710072F28C from the actor's position to `target` with `a8` as the
/// second tolerance. Placeholder name.
bool sub_710072F8E4(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a8);
/// 0x710072f944: sub_710072F28C from the actor's position to `target` with the given tolerances.
/// Placeholder name.
bool sub_710072F944(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, f32 a4);
/// 0x710072cb78 (declared only): sub_710072F28C from the actor's position (NaN) to `target` with the
/// tolerance `a3` and the other two default (-1); a4 is passed as the integer argument 5. Placeholder
/// name.
bool sub_710072CB78(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, s32 a4);
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

/// 0x710072e368 (declared only): navmesh-character check on Actor::m45(): false without one or when
/// the low half of its +0x2a4 word is 0x17; otherwise a virtual call (slot 4) on its +0x58 object,
/// or |sub_7100F74FD8(...)| <= a constant. Placeholder name.
bool sub_710072E368(ksys::act::Actor* actor);

/// 0x710072e304 (declared only; lane2 s21): whether `pos` is on a navmesh face found within `radius` (queries
/// HavokAI::sub_7100F87ED0 and the Unk_7100f7e9f0 result; false without a HavokAI instance). Placeholder name.
bool sub_710072E304(const sead::Vector3f& pos, f32 radius);

/// 0x710072ddb8: whether the direction from the translation of `mtx` to `target` is within `angle`
/// (radians) of the matrix's forward axis, both projected onto the XZ plane. Placeholder name.
bool sub_710072DDB8(const sead::Vector3f& target, const sead::Matrix34f& mtx, f32 angle);

/// 0x710072def0: whether `target` is within reach of an actor at `pos` facing `dir`: XZ distance
/// <= `max_dist`, height difference in [`min_dy`, `max_dy`], within `angle` of `dir` (checked only
/// beyond `angle_check_dist`), and no line-of-sight hit between the two points raised by
/// `y_offset`. Placeholder name; the float parameters' position among the vector ones is inferred
/// from the argument evaluation order of EnemyBaseFindPlayer::m35.
bool sub_710072DEF0(const sead::Vector3f& target, f32 max_dist, f32 min_dy, f32 max_dy,
                    const sead::Vector3f& pos, const sead::Vector3f& dir, f32 angle,
                    f32 angle_check_dist, f32 y_offset);

/// 0x710072e0a0: sub_710072DEF0 from the translation / forward axis of `mtx`, then a reachability
/// check (sub_710072E154) from the actor to `target`. False without an actor. Placeholder name.
bool sub_710072E0A0(ksys::act::Actor* actor, const sead::Vector3f& target,
                    const sead::Matrix34f& mtx, f32 max_dist, f32 min_dy, f32 max_dy, f32 angle,
                    f32 angle_check_dist, f32 y_offset);

/// 0x710072e928: world ray cast (RayCastBodyQuery, GroundHit 0xf, contact layer type 0, ground
/// layers from ksys::act::sub_7100EEACE8) from `from` to `to`, both raised by `y_offset`. On a hit,
/// writes the hit position / normal / material when the pointers are non-null. Placeholder name.
bool sub_710072E928(const sead::Vector3f& from, const sead::Vector3f& to, sead::Vector3f* hit_pos,
                    sead::Vector3f* hit_normal, ksys::phys::MaterialMask* material_mask,
                    f32 y_offset);

/// 0x710072eb10 (declared only): sub_710072E928 with the query's normal checking mode and, if `actor`
/// has physics, its system group handler (to ignore the actor itself). Placeholder name.
bool sub_710072EB10(const sead::Vector3f& from, const sead::Vector3f& to,
                    ksys::phys::RayCast::NormalCheckingMode mode, ksys::act::Actor* actor,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal, void* hit_info,
                    f32 y_offset);
/// 0x710072e5f8 / 0x710072e830 / 0x710072ea18: same with the layers of ksys::act::sub_7100EEAE58 /
/// sub_7100EEAECC / sub_7100EEACE8 and a normal checking mode (ksys::phys::RayCast::
/// NormalCheckingMode). Placeholder names.
bool sub_710072E5F8(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset);
bool sub_710072E830(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset);
bool sub_710072EA18(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset);
/// 0x710072e804: group handler `idx` (0 / 1) of the actor's physics instance set (null without one).
ksys::phys::SystemGroupHandler* sub_710072E804(ksys::act::Actor* actor, int idx);

// 0x71007398c0 (CSV Actor::x_50): the actor's spine controller (BoneControl::_0->_10) or nullptr; the
// same as Actor::sub_71011D8A10 but out of line in this TU.
ksys::act::Unk_7100d860d8* sub_71007398C0(ksys::act::Actor* actor);

/// 0x710072d53c: the RigidBody name of the actor's GiantArmorSlot GParamList slot (0 - 3; empty string otherwise).
const sead::SafeString& sub_710072D53C(ksys::act::Actor* actor, u32 slot);
