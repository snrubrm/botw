#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::act {
namespace ai {
class ActionBase;
class InlineParamPack;
}  // namespace ai
class Actor;
class BaseProc;
class BaseProcHandle;
class BaseProcLink;
class Unk_7100d860d8;
}  // namespace ksys::act

namespace uking::dmg {
class DamageManager;
}

namespace uking::act {
class Unk_71002dccbc;
class Weapon;
struct Unk_71002eda38;
struct Unk_71002edaec;
}  // namespace uking::act

class Unk_7102357d20;

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
/// 0x71005d91a0 (declared only; lane1 s21): checks the actor (an Enemy) against `value` (a depth /
/// distance; LandHumEnemyFindPlayer::enter_ passes NoBurnWaterDepth).
bool sub_71005D91A0(ksys::act::Actor* actor, f32 value);
/// 0x71005da5ac (lane1 s21): whether the weapon in slot `idx` (0 - 5) of the actor's ActorWeapons is
/// a Weapon whose chemical is in state 2 (Weapon::sub_71002E9A50); false otherwise.
bool sub_71005DA5AC(ksys::act::Actor* actor, int idx);
// 0x71005d8d4c (declared only): forwards to the object at Actor+0x548 (slot 8 -> slot 9 with
// `value` and `a2`; if `a3`, also slot 10 with (true, true)). AlertNearbyEnemies: noise level.
void sub_71005D8D4C(ksys::act::Actor* actor, f32 value, int idx, bool a3);
/// Whether the Enemy target is the player.
bool sub_71005D8FBC(ksys::act::Actor* actor);
/// Resets the Enemy target link and state.
void sub_71005D8E9C(ksys::act::Actor* actor);
/// Sets the Enemy target (Unk_7100013308::sub_71002DBC8C).
void sub_71005D8DE8(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link,
                    const sead::Matrix34f* mtx, const sead::Vector3f* pos);
/// 0x71005d8994 (CSV playerOrEnemyDropAllWeapons; declared only, lane3 s15): drops all weapons of a
/// PlayerOrEnemy (PlayerOrEnemy::dropAllWeapons, 0x78d4) with the given velocity; false for other actors.
bool playerOrEnemyDropAllWeapons(ksys::act::Actor* actor, const sead::Vector3f& velocity);
/// 0x71005d8748 (declared only, lane3 s15): dispatches on a PlayerOrEnemy / NPC cast to a weapon drop
/// (0x7a1c / 0x22554); `a5` is an object of unknown type (RTTI vtable 0x7102376d50, see lane4 s16 log).
bool sub_71005D8748(ksys::act::Actor* actor, const sead::Vector3f& velocity, bool a3, bool a4, void* a5,
                    bool a6);
/// Enemy target position (Vector3f::zero if not an Enemy).
const sead::Vector3f& sub_71005D9330(ksys::act::Actor* actor);
/// Position of the target actor (getField44C_Vec3), zero if there is none.
const sead::Vector3f& sub_71005D93CC(ksys::act::Actor* actor);
/// Velocity of the target actor, zero if not an Enemy.
const sead::Vector3f& sub_71005D9548(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D960C(ksys::act::Actor* actor);
/// 0x71005dfbe4 (declared only; lane1 s23): whether the enemy's target is within `dist` and `angle` (radians). Placeholder name.
bool sub_71005DFBE4(uking::act::Enemy* enemy, f32 dist, f32 angle);
const sead::Matrix34f& sub_71005D96A8(ksys::act::Actor* actor);
/// Enemy target state (0 if not an Enemy).
s32 sub_71005D9744(ksys::act::Actor* actor);
bool sub_71005D97D0(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D98D8(ksys::act::Actor* actor);
void sub_71005D9974(ksys::act::Actor* actor, u32 mask, bool set);

// --- other uking::act::Enemy fields ---

void sub_71005D7014(ksys::act::Actor* actor);
/// 0x71005d85c8 (CSV name; lane1 s22, declared only): drops weapon `idx` of a PlayerOrEnemy (or the
/// other actor class handled by 0x7100224f0): calls Weapon::m175(velocity, a4, a5, a6, a7) on the
/// equipped weapon. The type of `a6` is unknown (always null so far).
bool playerOrEnemyDropWeapon(ksys::act::Actor* actor, const sead::Vector3f* velocity, int idx,
                             bool a4, bool a5, void* a6, bool a7);
/// Enemy::_d70 or NPC::_e90 (nullptr otherwise).
uking::act::Unk_71002dccbc* sub_71005D9D68(ksys::act::Actor* actor);
/// Same as sub_71005D9D68 (a separate function that tail-calls it).
uking::act::Unk_71002dccbc* sub_71005D9E64(ksys::act::Actor* actor);
bool sub_71005DAFB0(ksys::act::Actor* actor);

// --- uking::act::NPC fields ---

/// NPCBase::_840 (nullptr if not an NPCBase).
void* sub_71005D77C8(ksys::act::Actor* actor);
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

/// Number of weapon slots of the actor (ActorWeapons::mWeapons), 0 if it has none.
s32 sub_71005D7854(ksys::act::Actor* actor);
/// PlayerOrEnemy::m163(idx) (false if not a PlayerOrEnemy).
bool sub_71005D8324(ksys::act::Actor* actor, int idx);
/// PlayerOrEnemy::m173() (false if not a PlayerOrEnemy).
bool sub_71005D9E68(ksys::act::Actor* actor);
// 0x71005d9f4c: AutoPlacementMgr::isNonAutoPlacement(pos, true); false without the manager.
bool sub_71005D9F4C(const sead::Vector3f& pos);
// 0x71005d9f70: the same for the actor's translation.
bool sub_71005D9F70(ksys::act::Actor* actor);
// 0x71005e0384: the actor has a LOD state whose _1c is not 1 and is more than 100 from the player.
bool sub_71005E0384(ksys::act::Actor* actor);

/// The actor in weapon slot `idx` if it is a uking::act::Weapon (nullptr otherwise).
uking::act::Weapon* sub_71005D83E8(ksys::act::Actor* actor, int idx);
/// 0x71005d8a30 (lane3 s18, declaration only; placeholder name, PullOut::handleMessage_): hands `weapon` to the
/// actor (the action depends on the actor's class: Enemy, NPC, ...).
void sub_71005D8A30(ksys::act::Actor* actor, uking::act::Weapon* weapon, bool a3);
/// Whether the weapon equipped in slot `idx` is a uking::act::Weapon with _d54 == 1 or 2.
bool sub_71005D8514(ksys::act::Actor* actor, int idx);
/// Whether none of the actor's weapon slots holds a uking::act::Weapon (false if it has no weapons).
bool sub_71005D8B60(ksys::act::Actor* actor);
/// Whether slot `idx` has an equipped weapon and ActorWeapons::mWeapons[idx]._10 is not set.
bool sub_71005DB904(ksys::act::Actor* actor, int idx);

// ActorWeapons::mWeapons[idx]._10

void sub_71005DB5C0(ksys::act::Actor* actor, int idx);
// 0x71005dbc94 (declared only; lane4 s23): Thrown / WillBallAttack / SetImpulseDamageMin /
// GanonBeastRoot::enter_ helper. If the actor's PhysicsUserTag (+0x528) is of a certain class (typeinfo
// GOT 0x7102578f08): sets the character controller's flag (true), every rigid body of the Body group
// to entity motion flag 8, and stores `a1` at +0x538, `a2` at +0x53c and the other flags as bits
// 1 / 4 / 8 / 0x10 of the byte at +0x53d.
void sub_71005DBC94(ksys::act::Actor* actor, s32 a1, bool a2, bool a3, bool a4, bool a5, bool a6);
void sub_71005DB6D0(ksys::act::Actor* actor, int idx);
bool sub_71005DB7E4(ksys::act::Actor* actor, int idx);

// --- misc ---

/// ActorCreator::mBlockSpawns (byte 0x59 of the ActorCreator instance).
bool sub_71005D6D10();
/// CSV name "Actor::callDeleteAndCreateDropAndEmit" (a free function in this file): calls
/// Actor::killWithDropsAndEffects(a1) unless the actor is being deleted.
void callDeleteAndCreateDropAndEmit(ksys::act::Actor* actor, int a1);
/// 0x71005e2b28 (declaration only; placeholder name): maps `value` (OnEnterSwapDropTableActor's DieType) to the
/// value stored in the actor's DropData `_4`.
s32 sub_71005E2B28(s32 value);
/// Sets bit 0 of a flag field (+0xc) in the actor's DropData (Actor vslot 134, RTTI 0x71025ae610),
/// then callDeleteAndCreateDropAndEmit(actor, false).
void sub_71005D6D48(ksys::act::Actor* actor);
/// Not decompiled (492 bytes; actor flag 0x51b bit 2, damage manager, Enemy::_e84 bit 0).
bool sub_71005D6E28(ksys::act::Actor* actor);
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
/// The bone control's look-at position (unchanged if the actor has no bone control).
void sub_71005DB4B8(sead::Vector3f* out, ksys::act::Actor* actor);
f32 sub_71005DB4DC(ksys::act::Actor* actor);
f32 sub_71005DB4FC(ksys::act::Actor* actor);
void sub_71005DB51C(ksys::act::Actor* actor, f32 a2, bool a3);
void sub_71005DB558(ksys::act::Actor* actor, f32 a2, bool a3);
void sub_71005DB594(ksys::act::Actor* actor, const sead::Vector3f& pos);
/// &BoneControl::_0->_10, or nullptr.
ksys::act::Unk_7100d860d8* sub_71005DB0EC(ksys::act::Actor* actor);

// --- Actor vtable slot 100 object (ksys::act::Unk_7100e4e084, DynamicActor+0x870) ---

void sub_71005DC270(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DC2B0(ksys::act::Actor* actor, const sead::Vector3f& pos, f32 a3, f32 a4);
void sub_71005DC30C(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DC350(ksys::act::Actor* actor, const sead::Vector3f& pos);
void sub_71005DC394(ksys::act::Actor* actor);
void sub_71005DC3CC(ksys::act::Actor* actor);
void sub_71005DC3F4(ksys::act::Actor* actor);
void sub_71005DC41C(ksys::act::Actor* actor);
bool sub_71005DC444(ksys::act::Actor* actor);
bool sub_71005DD1CC(ksys::act::Actor* actor, bool a2, f32 a3, f32 a4);
/// Whether the state (Unk_7100e4e084::_100) is 1 / 2 / 4 / 3 / 0.
bool sub_71005DC470(ksys::act::Actor* actor);
bool sub_71005DC49C(ksys::act::Actor* actor);
bool sub_71005DC4C8(ksys::act::Actor* actor);
bool sub_71005DC4F4(ksys::act::Actor* actor);
bool sub_71005DC520(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005DC54C(ksys::act::Actor* actor);
const sead::Matrix34f& sub_71005DC57C(ksys::act::Actor* actor);
const sead::SafeString& sub_71005DC5AC(ksys::act::Actor* actor);
void sub_71005DC5DC(ksys::act::Actor* actor);
void sub_71005DC604(ksys::act::Actor* actor, ksys::act::BaseProc* proc);
// 0x71005dc02c (declaration only; called by Thrown::leave_ when IsOnImpact).
void sub_71005DC02C(ksys::act::Actor* actor);
// 0x71005dc8ac (declaration only): writes a throw velocity to `out`; Thrown::calc_.
bool sub_71005DC8AC(ksys::act::Actor* actor, sead::Vector3f* out);
void sub_71005DC640(ksys::act::Actor* actor, ksys::act::BaseProcHandle* handle, int grab_idx);

// --- helpers using the typed Actor slots 97 (Chemical), 130 (ride info) ---

/// Chemical::_1b8 of the uking::act::Weapon equipped in slot `idx` (0-5), or 0.
f32 sub_71005DA668(ksys::act::Actor* actor, int idx);
/// Bit 2 of Chemical::_b8 of the Weapon equipped in slot `idx`.
bool sub_71005DA7F4(ksys::act::Actor* actor, int idx);
/// Whether Chemical::_1b8 of the Weapon equipped in slot `idx` is positive.
bool sub_71005DA8CC(ksys::act::Actor* actor, int idx);
/// 0x71005dd2e8: disables all attention clients except LockOn and AutoAim.
void sub_71005DD2E8(ksys::act::Actor* actor);
void sub_71005DD34C(ksys::act::Actor* actor, bool on);
/// 0x71005dcf80 (declaration only): ray cast along `dir` through the actor's position; stores a
/// texture index for the hit (terrain textures / material mask) in `material`. `a4` is unused.
bool sub_71005DCF80(s32* material, ksys::act::Actor* actor, const sead::Vector3f& dir, bool a4);
/// 0x71005dd27c (declaration only): uses texture index `material` for the actor's model.
void sub_71005DD27C(ksys::act::Actor* actor, u32 material, f32 a3);
/// The actor linked by the actor's ride info (Actor::getPlayerRideInfo), or nullptr.
ksys::act::Actor* sub_71005D7348(ksys::act::Actor* actor);

// --- misc ---

/// Bit 6 of Weapon::_e50 of the uking::act::Weapon in slot `idx`.
bool sub_71005D83C8(ksys::act::Actor* actor, int idx);
bool sub_71005D723C();
/// NPC flag 0x2000 of the actor `link` points to (ActorConstDataAccess::sub_7100022FD0).
bool sub_71005D777C(ksys::act::BaseProcLink* link);
/// 0x71005e1064: while the actor falls (velocity.y < 0), whether there is ground (sub_710072E5F8)
/// between its position and where its velocity takes it within one frame.
bool sub_71005E1064(ksys::act::Actor* actor);
bool sub_71005E116C(ksys::act::BaseProcLink* link);
// 0x71005e1630: sends `sender`'s message to the map objects linked to `actor` (only those whose unit
// config name is `name`, if not null/empty). One caller (BasicSignalEnemyForceNotice).
bool sub_71005E1630(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* name);
// 0x71005e02e0: sends `sender`'s message to the actor linked to `actor` by the
// "RegistedActorMessageBroadCastTag" link; stores that actor in `link` if not null. 11 callers.
bool sub_71005E02E0(ksys::act::Actor* actor, Unk_7102357d20* sender, ksys::act::BaseProcLink* link);
int sub_71005E2B28(int value);
// 0x71005e2318 / 0x71005e242c (declarations only): write a hit direction to `out` from the damage
// manager (DamageManagerBase::m30) or the actor's matrix (TakeHitImpactForce::m32 family).
void sub_71005E2318(sead::Vector3f* out, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr);
void sub_71005E242C(sead::Vector3f* out, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr);
void sub_71005E22D4(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f& dir,
                    f32 scale);
void sub_71005E01CC(ksys::act::Actor* actor, int a1, int a2);
/// The uking::act::Weapon equipped in slot `idx` (0-5), or nullptr.
uking::act::Weapon* sub_71005DA374(ksys::act::Actor* actor, int idx);
bool sub_71005DAF0C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int slot, int bank,
                    bool a5);
/// Enables or disables all ragdoll constraints of the actor.
void sub_71005E1B7C(ksys::act::Actor* actor, bool enable);
/// Resets Enemy::_f4c.
void sub_71005E21E8(ksys::act::Actor* actor);
/// Sets the keyframed state of the ragdoll bone `bone_name` (if the actor has a ragdoll and the bone exists).
void sub_71005E226C(ksys::act::Actor* actor, const sead::SafeString& bone_name, bool keyframed);
/// Whether the Weapon equipped in slot `idx` (0-5) has Weapon::_d54 == 1.
bool sub_71005DA9A8(ksys::act::Actor* actor, int idx);
/// Adds the position of the actor PlayerInfo::getSomeProcLink() links to (or zero) to `params`.
bool sub_71005D7270(ksys::act::ai::InlineParamPack* params, const char* key);
/// Sets bit 6 of Enemy::_e82.
void sub_71005E2C58(ksys::act::Actor* actor);
// 0x71005da304: the linked actor has the ObjectNightGlow tag and the environment exposure is ~0.
bool sub_71005DA304(ksys::act::BaseProcLink* link);
// 0x71005e2bcc: the enemy's Enemy::_12d0 object (nullptr for non-enemies).
uking::act::Enemy::Unk_12d0* sub_71005E2BCC(ksys::act::Actor* actor);
/// Normalised horizontal direction perpendicular to `dir` (ey x dir with y = 0).
void sub_71005E0230(sead::Vector3f* out, const ksys::act::Actor* actor, const sead::Vector3f& dir);
// --- attack helpers (used by the attack actions' calc_ and the Unk_71025afc58 family) ---
// Placeholder signatures from register use; the int arguments are forwarded to ASList (x / x_7).

/// Just-avoid setup: a3 is an angle (ignored if <= epsilon), a1/a2 distances, a4 is passed to
/// ASList::x.
void sub_71005DAB2C(ksys::act::Actor* actor, f32 a1, f32 a2, f32 a3, int a4);
bool sub_71005DD66C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int a2, int a3);
bool sub_71005DD74C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int a2, int a3);
/// Same as sub_71005DD66C / sub_71005DD74C with an explicit ASList::x type (they use 3).
bool sub_71005DD5B0(ksys::act::Actor* actor, int type, ksys::as::ASList::Unk4* query, int a3,
                    int a4);
bool sub_71005DD734(ksys::act::Actor* actor, int type, ksys::as::ASList::Unk4* query, int a3,
                    int a4);
bool sub_71005DD780(ksys::act::Actor* actor, int type, ksys::as::ASList::Unk4* query, int a3,
                    int a4);
bool sub_71005DD798(ksys::act::Actor* actor, int type, ksys::as::ASList::Unk4* query, int a3,
                    int a4);
bool sub_71005DD7B0(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int a2, int a3);
/// Build an Unk_71002edaec request (_0 = 2 / 1 / 0) and pass it to sub_71005D79AC. `name` and
/// `flags` may be null; flags is copied to Unk_71002edaec::_14.
void sub_71005D7F4C(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, f32 a6, f32 a7);
void sub_71005D7D90(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10);
void sub_71005D7ADC(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10);

// --- awareness / territory helpers used by EnemyNormal subclasses (lane1; declarations only) ---

/// Searches the actor's awareness entries within (dist, speed, angle); returns the found link.
ksys::act::BaseProcLink& sub_71005DE7F4(ksys::act::Actor* actor, f32 dist, f32 speed, f32 angle,
                                        bool a4);
/// Whether `link`'s actor is within (dist, speed, angle) of `actor`.
bool sub_71005DEC08(ksys::act::BaseProcLink* link, ksys::act::Actor* actor, f32 dist, f32 speed,
                    f32 angle);
/// 0x71005dbb60 (declared only): the weapon type (weapon actor +0xcf0) of the actor's weapon link
/// `idx` (0..5; Actor slot 98), or -1. Placeholder name.
s32 sub_71005DBB60(ksys::act::Actor* actor, s32 idx);
/// 0x71005df270 (declared only): the position of the actor's link (actor+0x7c8 links) whose map
/// object unit config name is `anchor_name`, offset by `dist`. Placeholder name.
void sub_71005DF270(sead::Vector3f* out, ksys::act::Actor* actor, const sead::SafeString& anchor_name,
                    f32 dist);
/// Sends `sender`'s message to the actors of the fortress tagged `tag` (no-op for an empty tag).
bool sub_71005E1884(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* tag);

// Placeholder name (after its only method, 0x71005e1be8; no ctor/vtable): four static-param strings
// of a Golem part (GolemRepairParts / GolemThrowPartsToTargetBase embed two, at +0x60 / +0xa0).
struct Unk_71005e1be8 {
    // 0x71005e1be8: loads the strings as static params whose names are formatted with `idx` + 1.
    void sub_71005E1BE8(ksys::act::ai::ActionBase* action, int idx);

    sead::SafeString _0;
    sead::SafeString _10;
    sead::SafeString _20;
    sead::SafeString _30;
};
