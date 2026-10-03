#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/Physics/System/physRayCast.h"

namespace ksys::act {
class Actor;
class BaseProcLink;
struct Struct8Base;
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
/// 0x7100738df0 (lane1 s22): whether the player is among the actor's attack contacts. Placeholder
/// name.
bool sub_7100738DF0(ksys::act::Actor* actor);
/// 0x7100738e70 (lane1 s22): whether the first body of the actor's rigid body set (by the name
/// from sub_71007A24D0) has a SensorPlayer contact. Placeholder name.
bool sub_7100738E70(ksys::act::Actor* actor);

// Single-branch functions of the same area forwarding to KingSystem actor utilities (0x7100ee5b84,
// 0x7100ee60ac). Names are placeholders.

/// Gravity acting on the actor (character controller gravity, or world gravity scaled by the main
/// rigid body's gravity factor).
void sub_710072DC50(sead::Vector3f* gravity, ksys::act::Actor* actor);

/// Inline-only in the original; names are guesses. The callers keep the result in the stack slot of the
/// gravity vector (SmallDamageBackwardBase::calc_, KnockBackShock::enter_, ...), i.e. these are
/// functions returning the vector by value.
inline sead::Vector3f getGravity(ksys::act::Actor* actor) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    return gravity;
}

/// The up direction for a gravity vector: the normalized negated vector (Y axis if it is null).
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

/// 0x71000891c8 (the one out-of-line copy of an inline function of the original; it sits in the
/// AirOctaFloatBase TU, ~35 callers): the actor's forward direction (matrix Z axis) with the
/// component along its up direction removed, normalised. Placeholder name.
void sub_71000891C8(sead::Vector3f* out, ksys::act::Actor* actor);

namespace uking::act {
class Dragon;
}

/// 0x7100010168 (out-of-line copy of an inline function, in the Dragon action TU; 6 Dragon AI callers):
/// the normalised direction from the dragon's reference position (+0x1e10) to its position, or the
/// X axis of its matrix at +0x1e28 if they coincide. Placeholder name.
void sub_7100010168(uking::act::Dragon* dragon, sead::Vector3f* out);

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
/// 0x710072fd0c (lane1 s22): sub_710072F28C without the normal output and with `a6 = false`; the fourth
/// float is not forwarded. Placeholder name.
bool sub_710072FD0C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7, f32 a8, f32 a9);
/// 0x710072f7ac (lane1 s22): sub_710072F28C with `a6 = true`, tolerance `a7` and default others;
/// writes the position to `out_pos`. Placeholder name.
bool sub_710072F7AC(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a7);
/// 0x710072f7d0 (lane1 s22): sub_710072F7AC with the tolerance taken from the actor's navmesh
/// character (`_2a8 * _2ac`, 0 without one). Placeholder name.
bool sub_710072F7D0(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5);
/// 0x710072f788: sub_710072F28C from `from` to `to` with default tolerances; writes the position to
/// `out_pos`. Placeholder name.
bool sub_710072F788(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos);
/// 0x710072f944: sub_710072F28C from the actor's position to `target` with the given tolerances.
/// Placeholder name.
bool sub_710072F944(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, f32 a4);
/// 0x710072f8e4: sub_710072F28C from the actor's position to `target`, the tolerance `a3` in the second
/// float slot. Placeholder name.
bool sub_710072F8E4(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3);
/// 0x710072dc9c: sets the gravity factor of the actor's character controller, or of its main body
/// without one. Placeholder name.
void sub_710072DC9C(ksys::act::Actor* actor, f32 factor);
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
/// 0x710072b85c (CSV name; lane1 s22): the player's actor matrix (identity without a PlayerInfo).
/// The reference points into the actor, not into a copy.
const sead::Matrix34f& getPlayerPositionViaPlayerInfo();
/// 0x710073d318 (lane1 s22): the actor's rider (the actor behind its HorseRideInfo link), if any.
/// Placeholder name.
ksys::act::Actor* sub_710073D318(ksys::act::Actor* actor);
/// 0x710073b870 (CSV name, sic; lane1 s22, declared only): starts the get-item demo for the actor
/// (emits the get-demo sound when `a2`); false when the actor is not in a state to start it.
bool triggereGetItemDemoMaybe(ksys::act::Actor* actor, bool a2, bool a3);
/// 0x7100734270 (lane1 s22): copies `pos` to `out` and sets bit 0x80 in the actor's DropData flags
/// (DropData::m5() reads it); false without DropData. Name is a placeholder.
bool sub_7100734270(ksys::act::Actor* actor, sead::Vector3f* out, const sead::Vector3f& pos);
// 0x710072e280 (CSV name): casts a world ray from `pos` to `pos + dir * distance` (the TU after
// uking::Unk_71024739d0, sub_710090DB04); writes the hit position.
bool somePositionCalc(sead::Vector3f* hit_position, const sead::Vector3f& pos,
                      const sead::Vector3f& dir, f32 distance);

/// 0x710072e368 (declared only): navmesh-character check on Actor::m45(): false without one or when
/// the low half of its +0x2a4 word is 0x17; otherwise a virtual call (slot 4) on its +0x58 object,
/// or |sub_7100F74FD8(...)| <= a constant. Placeholder name.
bool sub_710072E368(ksys::act::Actor* actor);

/// 0x710072dcfc (lane1 s22): whether the XZ direction from `pos` to `target` is within `angle` (radians)
/// of `dir` (dot product of the normalised XZ direction with `dir` >= cos(angle)). Placeholder name.
bool sub_710072DCFC(const sead::Vector3f& target, const sead::Vector3f& pos,
                    const sead::Vector3f& dir, f32 angle);

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

/// sub_710072DEF0 from the translation / forward axis of `mtx` (copied into locals before the call,
/// after the other arguments are evaluated).
/// inline-only in the original; name is a guess. Evidence: the same sequence (params first, then the
/// translation copied element-wise via an out-param and the forward axis) is inlined into
/// sub_710072E0A0, EnemyBaseFindPlayer::m35 and FlyingEnemyFindPlayer::m35.
inline bool inlineIsTargetInReach(const sead::Vector3f& target, f32 max_dist, f32 min_dy,
                                  f32 max_dy, const sead::Matrix34f& mtx, f32 angle,
                                  f32 angle_check_dist, f32 y_offset) {
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    const sead::Vector3f dir = mtx.getBase(2);
    return sub_710072DEF0(target, max_dist, min_dy, max_dy, pos, dir, angle, angle_check_dist,
                          y_offset);
}

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

/// 0x7100739578 (lane1 s22): the attack info the actor's attack sensor reports (a DynamicCast'ed
/// object's +0x6c selects it; falls back to ActorAtk entry 0 when the actor has attack info), or
/// null. Its first three floats are the attack position. Placeholder name.
const ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_7100739578(ksys::act::Actor* actor);

/// 0x710073de08 (lane1 s22): clears stasis flags 0x10 and 0x4 (Actor 0x71011d0228) and sets
/// ActorFlag2 0x10000. Placeholder name.
void sub_710073DE08(ksys::act::Actor* actor);
/// 0x710073de44: the opposite: sets stasis flags 0x10 and 0x4 (Actor 0x71011d0204) and clears
/// ActorFlag2 0x10000. Placeholder name.
void sub_710073DE44(ksys::act::Actor* actor);

/// 0x7100731000 (lane1 s22): sets the map unit param "IsPlayerPut" (bool) of the actor's root AI;
/// false if the actor has no such param. Placeholder name.
bool sub_7100731000(ksys::act::Actor* actor, bool value);
