#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

namespace uking::act {
class Unk_71002dccbc;
struct Unk_71002eda38;
struct Unk_71002edaec;
}  // namespace uking::act

// Free helper functions of an unnamed AI utility translation unit (0x71005d6d10 - 0x71005e2f3c,
// linked between aiUrbosasFuryDamageSelector and aiVacuumedBombDamageSelect). Most of them take an
// actor, DynamicCast it (e.g. to uking::act::Enemy) and access the result.
// Names are placeholders (sub_<address>) unless the CSV had one; setDamageCallbackTiming and
// sub_71005DA114 (also in this file) are declared in Game/Damage/dmgDamageCallback.h.

// --- uking::act::Enemy target (Enemy::_c48) ---

/// Enemy target link, or nullptr if the actor is not an Enemy.
ksys::act::BaseProcLink* sub_71005D9050(ksys::act::Actor* actor);
/// Enemy target link, or a global empty BaseProcLink if the actor is not an Enemy.
ksys::act::BaseProcLink& sub_71005D94AC(ksys::act::Actor* actor);
/// Whether the Enemy has a target (link has a proc).
bool sub_71005D8F28(ksys::act::Actor* actor);
/// Whether the Enemy target is the player.
bool sub_71005D8FBC(ksys::act::Actor* actor);
/// Resets the Enemy target link and state.
void sub_71005D8E9C(ksys::act::Actor* actor);
/// Sets the Enemy target (Unk_7100013308::sub_71002DBC8C).
void sub_71005D8DE8(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link,
                    const sead::Matrix34f* mtx, const sead::Vector3f* pos);
/// Enemy target position (Vector3f::zero if not an Enemy).
const sead::Vector3f& sub_71005D9330(ksys::act::Actor* actor);
/// Position of the target actor (getField44C_Vec3), zero if there is none.
const sead::Vector3f& sub_71005D93CC(ksys::act::Actor* actor);
/// Velocity of the target actor, zero if not an Enemy.
const sead::Vector3f& sub_71005D9548(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D960C(ksys::act::Actor* actor);
const sead::Matrix34f& sub_71005D96A8(ksys::act::Actor* actor);
/// Enemy target state (0 if not an Enemy).
s32 sub_71005D9744(ksys::act::Actor* actor);
bool sub_71005D97D0(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D98D8(ksys::act::Actor* actor);
void sub_71005D9974(ksys::act::Actor* actor, u32 mask, bool set);

// --- other uking::act::Enemy fields ---

void sub_71005D7014(ksys::act::Actor* actor);
/// Enemy::_d70 or NPC::_e90 (nullptr otherwise).
uking::act::Unk_71002dccbc* sub_71005D9D68(ksys::act::Actor* actor);
bool sub_71005DAFB0(ksys::act::Actor* actor);

// --- uking::act::NPC fields ---

/// Sets or clears bit 7 of NPC::_fe8.
void sub_71005D7518(ksys::act::Actor* actor, bool set);
/// Bit 7 of NPC::_fe8 (false if not an NPC).
bool sub_71005D75B4(ksys::act::Actor* actor);
/// Sets or clears bit 10 of NPC::_fe8.
void sub_71005D7644(ksys::act::Actor* actor, bool set);
/// Sets or clears bit 13 of NPC::_fe8.
void sub_71005D76E0(ksys::act::Actor* actor, bool set);

// --- PlayerOrEnemy / NPC weapons ---

/// Passes `arg` to the weapon equipped in slot `idx` (PlayerOrEnemy::sub_7100007CA8 or
/// NPC::sub_71000225B0). Does nothing if idx < 0.
void sub_71005D787C(ksys::act::Actor* actor, int idx, const uking::act::Unk_71002eda38& arg);
/// Same for Unk_71002edaec (PlayerOrEnemy::sub_7100007D58 or NPC::sub_7100022660).
void sub_71005D79AC(ksys::act::Actor* actor, int idx, const uking::act::Unk_71002edaec& arg);
/// Builds an Unk_71002eda38 request of type 6 / 7 and passes it to sub_71005D787C.
void sub_71005D80FC(ksys::act::Actor* actor, int idx, const sead::Vector3f& pos, int a3, f32 a4,
                    const sead::Vector3f* pos2, const ksys::act::BaseProcLink* link);
void sub_71005D8210(ksys::act::Actor* actor, int idx, const sead::Vector3f& pos, int a3, f32 a4,
                    const sead::Vector3f* pos2, const ksys::act::BaseProcLink* link);

// ActorWeapons::mWeapons[idx]._10

void sub_71005DB5C0(ksys::act::Actor* actor, int idx);
void sub_71005DB6D0(ksys::act::Actor* actor, int idx);
bool sub_71005DB7E4(ksys::act::Actor* actor, int idx);

// --- misc ---

/// ActorCreator::mBlockSpawns (byte 0x59 of the ActorCreator instance).
bool sub_71005D6D10();
/// CSV name "Actor::callDeleteAndCreateDropAndEmit" (a free function in this file): calls
/// Actor::killWithDropsAndEffects(a1) unless the actor is being deleted.
void callDeleteAndCreateDropAndEmit(ksys::act::Actor* actor, int a1);
/// Sets bit 0 of a flag field (+0xc) in the actor's DropData (Actor vslot 134, RTTI 0x71025ae610),
/// then callDeleteAndCreateDropAndEmit(actor, false).
void sub_71005D6D48(ksys::act::Actor* actor);
/// Whether the actor's map object has rails.
bool sub_71005D9F04(ksys::act::Actor* actor);

// --- Actor::mBoneControl (Actor+0x5a0) helpers ---
// They operate on the object the BoneControl's first member points to (methods 0x7100d83014,
// 0x7100d8571c, 0x7100d85750, 0x7100d85774, ...; flags at +0x9c (u16) / +0xe4 (u32), target position
// at +0x18). Most callers are look-at/turn AI.

void sub_71005D73F8(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005D7444(ksys::act::Actor* actor, const sead::Vector3f& pos, bool a3, bool a4);
void sub_71005D74B8(ksys::act::Actor* actor);
void sub_71005D74E8(ksys::act::Actor* actor);
void sub_71005DB068(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DB0A8(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DB110(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DB198(sead::Vector3f* pos, ksys::act::Actor* actor);
void sub_71005DB1D8(ksys::act::Actor* actor, const sead::Vector3f& pos);
/// Like sub_71005DB1D8 with the Enemy target (Enemy::_c48._18 / _54).
void sub_71005DB248(ksys::act::Actor* actor);
void sub_71005DB3B8(ksys::act::Actor* actor);
void sub_71005DB3EC(ksys::act::Actor* actor);
void sub_71005DB404(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DB41C(ksys::act::Actor* actor);
void sub_71005DB434(ksys::act::Actor* actor);
void sub_71005DB44C(ksys::act::Actor* actor, f32 a2, f32 a3);
void sub_71005DB498(ksys::act::Actor* actor);
f32 sub_71005DB4DC(ksys::act::Actor* actor);
f32 sub_71005DB4FC(ksys::act::Actor* actor);
void sub_71005DB51C(ksys::act::Actor* actor, f32 a2, bool a3);
void sub_71005DB558(ksys::act::Actor* actor, f32 a2, bool a3);
void sub_71005DB594(ksys::act::Actor* actor, const sead::Vector3f& pos);
