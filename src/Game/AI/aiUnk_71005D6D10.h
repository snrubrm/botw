#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
namespace ai {
class InlineParamPack;
}  // namespace ai
class Actor;
class BaseProc;
class BaseProcLink;
class Unk_7100d860d8;
}  // namespace ksys::act

namespace uking::act {
class Unk_71002dccbc;
class Weapon;
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

/// The actor in weapon slot `idx` if it is a uking::act::Weapon (nullptr otherwise).
uking::act::Weapon* sub_71005D83E8(ksys::act::Actor* actor, int idx);
/// Whether the weapon equipped in slot `idx` is a uking::act::Weapon with _d54 == 1 or 2.
bool sub_71005D8514(ksys::act::Actor* actor, int idx);
/// Whether none of the actor's weapon slots holds a uking::act::Weapon (false if it has no weapons).
bool sub_71005D8B60(ksys::act::Actor* actor);
/// Whether slot `idx` has an equipped weapon and ActorWeapons::mWeapons[idx]._10 is not set.
bool sub_71005DB904(ksys::act::Actor* actor, int idx);

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

// --- helpers using the typed Actor slots 97 (Chemical), 130 (ride info) ---

/// Chemical::_1b8 of the uking::act::Weapon equipped in slot `idx` (0-5), or 0.
f32 sub_71005DA668(ksys::act::Actor* actor, int idx);
/// Bit 2 of Chemical::_b8 of the Weapon equipped in slot `idx`.
bool sub_71005DA7F4(ksys::act::Actor* actor, int idx);
/// Whether Chemical::_1b8 of the Weapon equipped in slot `idx` is positive.
bool sub_71005DA8CC(ksys::act::Actor* actor, int idx);
void sub_71005DD34C(ksys::act::Actor* actor, bool on);
/// The actor linked by the actor's ride info (Actor::getPlayerRideInfo), or nullptr.
ksys::act::Actor* sub_71005D7348(ksys::act::Actor* actor);

// --- misc ---

/// Bit 6 of Weapon::_e50 of the uking::act::Weapon in slot `idx`.
bool sub_71005D83C8(ksys::act::Actor* actor, int idx);
bool sub_71005D723C();
bool sub_71005DD734(ksys::act::Actor* actor, int a1, const sead::SafeString& name, int slot,
                    int bank);
bool sub_71005DD74C(ksys::act::Actor* actor, const sead::SafeString& name, int slot, int bank);
bool sub_71005DD780(ksys::act::Actor* actor, int a1, const sead::SafeString& name, int slot,
                    int bank);
bool sub_71005DD798(ksys::act::Actor* actor, int a1, const sead::SafeString& name, int slot,
                    int bank);
bool sub_71005DD7B0(ksys::act::Actor* actor, const sead::SafeString& name, int slot, int bank);
bool sub_71005E116C(ksys::act::BaseProcLink* link);
int sub_71005E2B28(int value);
void sub_71005E22D4(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f& dir,
                    f32 scale);
void sub_71005E01CC(ksys::act::Actor* actor, int a1, int a2);
/// The uking::act::Weapon equipped in slot `idx` (0-5), or nullptr.
uking::act::Weapon* sub_71005DA374(ksys::act::Actor* actor, int idx);
bool sub_71005DAF0C(ksys::act::Actor* actor, const sead::SafeString& name, int slot, int bank,
                    bool a5);
bool sub_71005DD5B0(ksys::act::Actor* actor, int a1, const sead::SafeString& name, int slot,
                    int bank);
/// Enables or disables all ragdoll constraints of the actor.
void sub_71005E1B7C(ksys::act::Actor* actor, bool enable);
/// Resets Enemy::_f4c.
void sub_71005E21E8(ksys::act::Actor* actor);
/// Whether the Weapon equipped in slot `idx` (0-5) has Weapon::_d54 == 1.
bool sub_71005DA9A8(ksys::act::Actor* actor, int idx);
/// Adds the position of the actor PlayerInfo::getSomeProcLink() links to (or zero) to `params`.
bool sub_71005D7270(ksys::act::ai::InlineParamPack* params, const char* key);
bool sub_71005DD66C(ksys::act::Actor* actor, const sead::SafeString& name, int slot, int bank);
/// Sets bit 6 of Enemy::_e82.
void sub_71005E2C58(ksys::act::Actor* actor);
/// Normalised horizontal direction perpendicular to `dir` (ey x dir with y = 0).
void sub_71005E0230(sead::Vector3f* out, const ksys::act::Actor* actor, const sead::Vector3f& dir);
// --- attack helpers (used by the attack actions' calc_ and the Unk_71025afc58 family) ---
// Placeholder signatures from register use; the int arguments are forwarded to ASList (x / x_7).

/// Just-avoid setup: a3 is an angle (ignored if <= epsilon), a1/a2 distances, a4 is passed to
/// ASList::x.
void sub_71005DAB2C(ksys::act::Actor* actor, f32 a1, f32 a2, f32 a3, int a4);
bool sub_71005DD66C(ksys::act::Actor* actor, const sead::SafeString* name, int a2, int a3);
bool sub_71005DD74C(ksys::act::Actor* actor, const sead::SafeString* name, int a2, int a3);
/// Build an Unk_71002edaec request (_0 = 2 / 1 / 0) and pass it to sub_71005D79AC. `name` and
/// `flags` may be null; flags is copied to Unk_71002edaec::_14.
void sub_71005D7F4C(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, f32 a6, f32 a7);
void sub_71005D7D90(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10);
void sub_71005D7ADC(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10);
