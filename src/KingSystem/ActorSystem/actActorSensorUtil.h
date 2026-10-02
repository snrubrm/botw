#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

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

// --- ActorAtk ---
// 0x71007a255c (CSV Actor::x_46): ActorAtk::sub_710079E2C0(idx).
const ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_71007A255C(ksys::act::Actor* actor, int idx);
// 0x71007a28dc (CSV Actor::getAttackInfo): ActorAtk::getAttackInfo(idx).
const ksys::act::ActorAtk::Struct7::AttackInfo* getAttackInfo(ksys::act::Actor* actor, int idx);
// 0x71007a2604 (CSV Actor::x_52): ActorAtk::m10().
bool sub_71007A2604(ksys::act::Actor* actor);
// 0x71007a26ac: ActorAtk::sub_710079E270().
s32 sub_71007A26AC(ksys::act::Actor* actor);
// 0x71007a2984 (CSV): ActorAtk::hasAttackInfoMaybe().
bool hasAttackInfo(ksys::act::Actor* actor);
// 0x71007a2a2c (CSV Actor::getNumAttackInfoMaybe).
s32 getNumAttackInfoMaybe(ksys::act::Actor* actor);
// 0x71007a2acc (CSV): ActorAtk::_40.
void* getActorAttackSensor(ksys::act::Actor* actor);
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
