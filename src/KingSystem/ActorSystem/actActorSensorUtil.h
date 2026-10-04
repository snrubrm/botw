#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace ksys::act {
class Actor;
class AttackSensor;
class AttackSensor2Listener;
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
class SystemGroupHandler;
}  // namespace ksys::phys

// Helpers around an actor's attack info (Actor::getAtk() -> ActorAtk) and its slot-126 object
// (Actor::m126() -> Unk_7102459df8), TU 0x71007a21d4-0x71007a4bd8. Names are the CSV names where
// it has one (namespace unknown; CSV "Actor::*" / "PlayerOrEnemy::*" entries are free functions
// taking the actor), `sub_<ADDR>` otherwise.

// --- rigid body / sensor group names ---
// 0x71007a24bc-0x71007a2548 (CSV getStr_Atk_0, getStr_Tgt_0, getStr_Body_0, j_getStr_Chemical, ...): the
// ksys::act::getStr_* names as pointers (the return type differs, so the calls are not tail calls).
const sead::SafeString* sub_71007A24BC();  // getStr_Atk
const sead::SafeString* sub_71007A24D0();  // getStr_Tgt
const sead::SafeString* sub_71007A24E4();  // getStr_Body
const sead::SafeString* sub_71007A24F8();  // getStr_Chemical
const sead::SafeString* sub_71007A250C();  // getStr_EntitySensor
const sead::SafeString* sub_71007A2520();  // getStr_Secure
const sead::SafeString* sub_71007A2534();  // getStr_Lod
const sead::SafeString* sub_71007A2548();  // getStr_GeneralSensor

// 0x71007a397c: sets the contact layer of every body of the actor's "Tgt" rigid body set to
// SensorQueryOnly (if the actor has attack info).
void sub_71007A397C(ksys::act::Actor* actor);

// --- "Atk" / "Tgt" rigid bodies (0x71007a2d34-0x71007a3978) ---
// Activates an "Atk" body: optional new transform, added to the world, and its AttackSensor user
// tag gets _44 incremented and _49 set (2B64); the body `name` (2C30); all bodies (2C9C).
void sub_71007A2B64(ksys::phys::RigidBody* body, const sead::Matrix34f* mtx);
// 0x71007a2eb0: restores the contact layer / ground hit of an attack sensor body from the owner's
// physics parameters (with `handler` as system group handler) and counts the activation.
void sub_71007A2EB0(ksys::phys::RigidBody* body, ksys::act::Actor* actor,
                    ksys::phys::SystemGroupHandler* handler);
void sub_71007A2C30(ksys::act::Actor* actor, const sead::SafeString& name,
                    const sead::Matrix34f* mtx);
// 0x71007a302c: body `name` of the "Atk" set: re-registered in the instance set with `handler` as
// its system group handler and counted as an activation of its AttackSensor.
void sub_71007A302C(ksys::act::Actor* actor, const sead::SafeString& name,
                    ksys::phys::SystemGroupHandler* handler);
void sub_71007A2C9C(ksys::act::Actor* actor);
// Single bodies: removed from / added to the physics world when needed.
void sub_71007A2D34(ksys::phys::RigidBody* body);  // remove
void sub_71007A3470(ksys::phys::RigidBody* body);  // add
void sub_71007A35EC(ksys::phys::RigidBody* body);  // remove
void sub_71007A3258(ksys::phys::RigidBody* body, ksys::phys::SystemGroupHandler* handler);
void sub_71007A3900(ksys::phys::RigidBody* body);  // SensorQueryOnly
// The body `name` of the actor's "Atk" set: remove (2D7C), contact layer SensorNoHit with
// `handler` (3270); all "Atk" bodies: remove (2E04).
void sub_71007A2D7C(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_71007A2E04(ksys::act::Actor* actor);
// 0x71007a3a8c (declaration only; lane3 s22; 1.2 KB): the AttackDirType value of a name (-1 for null / empty).
int sub_71007A3A8C(const sead::SafeString* name);
// 0x71007a32e4 (declaration only; lane3 s20): all "Atk" bodies get contact layer 0x35 with `handler`
// (setContactLayerAndHandler).
void sub_71007A32E4(ksys::act::Actor* actor, ksys::phys::SystemGroupHandler* handler);
void sub_71007A3270(ksys::act::Actor* actor, const sead::SafeString& name,
                    ksys::phys::SystemGroupHandler* handler);
// The body `name` of the actor's "Tgt" set: add (34B8), remove (3634), SensorQueryOnly (3910);
// all "Tgt" bodies: add (3540), remove (36BC, CSV Actor::x_56).
void sub_71007A34B8(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_71007A3540(ksys::act::Actor* actor);
void sub_71007A3634(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_71007A36BC(ksys::act::Actor* actor);
void sub_71007A3910(ksys::act::Actor* actor, const sead::SafeString& name);
// InstanceSet::sub_7100FBAF18(body) on the actor's physics (3768) / on the "Tgt" body `name` (3778).
void sub_71007A3768(ksys::act::Actor* actor, ksys::phys::RigidBody* body);
// Clears AttackSensor2::_38 and calls InstanceSet::sub_7100FBB18C on the "Tgt" body set.
void sub_71007A3800(ksys::act::Actor* actor);
void sub_71007A3778(ksys::act::Actor* actor, const sead::SafeString& name);

// --- ActorAtk ---
// 0x71007a255c (CSV Actor::x_46): ActorAtk::sub_710079E2C0(idx).
ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_71007A255C(ksys::act::Actor* actor, int idx);
// 0x71007a28dc (CSV Actor::getAttackInfo): ActorAtk::getAttackInfo(idx).
ksys::act::ActorAtk::Struct7::AttackInfo* getAttackInfo(ksys::act::Actor* actor, int idx);
// 0x71007a2604 (CSV Actor::x_52): ActorAtk::m10().
bool sub_71007A2604(ksys::act::Actor* actor);
// 0x71007a274c (CSV Actor::x_47): whether ActorAtk::m10() and one of its sub_710079E2C0 entries has
// any of the bits 0x1f81f in _50.
bool sub_71007A274C(ksys::act::Actor* actor);
// 0x71007a26ac: ActorAtk::sub_710079E270().
s32 sub_71007A26AC(ksys::act::Actor* actor);
// 0x71007a2984 (CSV): ActorAtk::hasAttackInfoMaybe().
bool hasAttackInfo(ksys::act::Actor* actor);
// 0x71007a2a2c (CSV Actor::getNumAttackInfoMaybe).
s32 getNumAttackInfoMaybe(ksys::act::Actor* actor);
// 0x71007a2acc (CSV): ActorAtk::_40.
ksys::act::AttackSensor* getActorAttackSensor(ksys::act::Actor* actor);
// 0x71007a439c / 0x71007a4440: ActorAtk::sub_710079E344 / sub_710079E3B8 (behaviors SetThroughArrow / SetThroughCloseWeapon).
void sub_71007A439C(ksys::act::Actor* actor, ksys::act::AttackSensor2Listener* listener);
void sub_71007A4440(ksys::act::Actor* actor, ksys::act::AttackSensor2Listener* listener);
// 0x71007a44e4 / 0x71007a458c: set or clear bit 0 / bit 1 of ActorAtk::_78.
void sub_71007A44E4(ksys::act::Actor* actor, bool on);
void sub_71007A458C(ksys::act::Actor* actor, bool on);

// --- Unk_7102459df8 (Actor::m126) ---
// 0x71007a40d0 (CSV PlayerOrEnemy::x_24)
ksys::act::Unk_7102459df8::Unk_710079d5a0::Unk1* sub_71007A40D0(ksys::act::Actor* actor, int idx);
// 0x71007a4178: Unk_7102459df8::sub_710079CEE8() (false when `ignore_creator` and the first contact
// is the actor's creator).
bool sub_71007A4178(ksys::act::Actor* actor, bool ignore_creator);
// 0x71007a425c
s32 sub_71007A425C(ksys::act::Actor* actor);
// 0x71007a42fc
bool sub_71007A42FC(ksys::act::Actor* actor);
// 0x71007a4638 (CSV Actor::isLandedMaybe): Unk_7102459df8::sub_710079CE78(), same creator check.
bool isLandedMaybe(ksys::act::Actor* actor, bool ignore_creator);
// 0x71007a471c
ksys::act::Unk_7102459df8::Unk_7102459e60::Unk1* sub_71007A471C(ksys::act::Actor* actor, int idx);
// 0x71007a47c4
s32 sub_71007A47C4(ksys::act::Actor* actor);
// 0x71007a4864 (CSV Actor::isBgGroundHit): Unk_7102459df8::sub_710079CEB0(), same creator check.
bool isBgGroundHit(ksys::act::Actor* actor, bool ignore_creator);
// 0x71007a4948
ksys::act::Unk_7102459df8::Unk_7102459e88::Unk1* sub_71007A4948(ksys::act::Actor* actor, int idx);
// 0x71007a49f0
s32 sub_71007A49F0(ksys::act::Actor* actor);
