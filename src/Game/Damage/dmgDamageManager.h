#pragma once

#include <container/seadRingBuffer.h>

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/Damage/dmgDamageMgrNPC.h"
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
}

namespace uking::dmg {

// CSV: DamageMgr (vtable 0x710244ddf8, 57 slots; ctor 0x71006d23e0). RTTI static 0x71025ae600.
// TODO: incomplete. Size 0x230 (the ctor's last store is at 0x228; Horse embeds one at 0xd20
// followed by a member at 0xf50).
// Placeholder (the object at DamageManager::_220; only the field read by sub_71006D8534).
struct DamageManagerHit {
    /* 0x00 */ s32 _0;
    /* 0x04 */ u8 _4[0xc];
    /* 0x10 */ s32 _10;
    /* 0x14 */ s32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1c */ u8 _1c[0x4c - 0x1c];
};
KSYS_CHECK_SIZE_NX150(DamageManagerHit, 0x4c);

// Placeholder (the object at DamageManager::_220): starts with the ring buffer of the recent damage records (0x4c bytes
// each; the accessors below read the most recent one).
struct DamageManagerUnk220 {
    // 0x71006d9a24 / 0x71006d9b30 (lane4 s48; placeholder names): the fraction of the recorded hits (`size / capacity`),
    // or with `_27a` the stasis blow speed over the player's speed limit (clamped to 0.01 .. 1.0 in that case) for the
    // `getter()` value of the actor (Actor::m38 / ActorConstDataAccess::sub_7100D14114).
    f32 sub_71006D9A24(ksys::act::Actor* actor) const;
    f32 sub_71006D9B30(const ksys::act::ActorConstDataAccess& accessor) const;

    /* 0x000 */ sead::RingBuffer<DamageManagerHit> mHits;
    /* 0x018 */ u8 _18[0x27a - 0x18];
    /* 0x27a */ bool _27a;
    /* 0x27c */ sead::Vector3f _27c;
};

// Message senders embedded in DamageManager (0xd8: message 0x800003e, 0x128: message 0x800003f; no payload, m2 returns
// null). Placeholder names = vtables 0x710244e030 / 0x710244e058 (D0 0x71006d9664 / 0x71006d9670).
class Unk_710244e030 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class Unk_710244e058 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class DamageManager : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageManager, DamageManagerBase)
public:
    explicit DamageManager(ksys::act::Actor* actor);
    void preDelete1() override;
    // 0x71006d263c (CSV DamageMgr::m20; declared only): the base reset, resetStuff, then its own state.
    void resetDamage() override;
    // 0x71006d22d0 (CSV DamageMgr::m23): the two Struct20 objects are Struct20_2 (their constructor is inlined here).
    bool allocStruct20(sead::Heap* heap) override;
    // 0x71006d8520: 1 while _8c has bit 4, else the base class's table lookup.
    s32 m49(s32 damageTypeMaybe) override;
    // Overrides of the base slots (lane4 s47; CSV DamageMgr::m18 / checkDamageFlags / m42 / m39 / m40 / m41).
    s32 getNumCallbacks() override;
    bool checkDamageFlags(s32 bit) override;
    bool m42() override;
    // Slot 13 (CSV DamageMgr::m13): the stasis blow ratio of `_220` (0 without it).
    f32 m13() override;
    bool m14(sead::Vector3f* out) override;
    bool isSlowTime() override;
    bool m40(s32* out) override;
    bool m41() override;
    bool m38(ksys::phys::RigidBody* body) override;
    // Slot 45 (0x71006d85a8): applies a condition damage (kind 2 / 4: m54 / m55, kind 3: sub_71006D888C, the others
    // through sub_71006D357C with event 5).
    void m45(const ConditionDamageInfo& info) override;
    // Slot 46 (0x71006d6b5c): the base handling, then the flags, guard state and scaled direction (_cc) of the
    // Struct20_2 in mStruct20_b.
    void handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6) override;
    // Slot 16 (0x71006d8404): the listeners _f0, _140 and _1a8 (the last one inlined).
    bool m16(const ksys::Message& message) override;
    // Slots 29 / 30 (CSV DamageMgr::m29 / m30): the normalised `_cc` for damage kind 7 when bit 6 of `_216` is set,
    // else the base class.
    bool m29(sead::Vector3f* out) override;
    bool m30(sead::Vector3f* out) override;
    // Slots 33 / 34 (CSV DamageMgr::m33 / m34): the material masks of the attack info (`_20` / `_38`) or null.
    ksys::phys::MaterialMask* m33() override;
    ksys::phys::MaterialMask* tgSensorMaterialOnHitMaybe() override;
    // Slot 27 (CSV DamageMgr::getPosition): the actor's position, replaced by the position of the damage kind (the attack
    // info's position, `_90`, the impulse data, the position moved against the damage direction or the velocity).
    bool getPosition(sead::Vector3f* out) override;
    // Slot 28 (CSV DamageMgr::m28): a direction depending on the damage kind (the attack info's `_c`, `_c0`, `_cc`, `_9c`, the
    // impulse data, the actor's velocity or z axis); false for the others.
    bool getAttackPos(sead::Vector3f* out) override;
    // Slot 31 (CSV DamageMgr::m31): like getAttackPos with the attack info's `_94`, `_a8` and normalised directions.
    bool m31(sead::Vector3f* out) override;
    // Slot 32 (CSV DamageMgr::m32): the blow vector of the damage kind (the attack info's `_a0`, `_c` / the negated velocity scaled
    // by 600 / 1800, the impulse data, `_cc`, `_b4`).
    bool m32(sead::Vector3f* out) override;
    // Slot 35 (CSV DamageMgr::m35): the matrix of the attacker of the damage kind (the attack info's link actor, the attack
    // info's matrix, or the actor's impulse data); false (identity) otherwise.
    bool m35(sead::Matrix34f* out) override;
    // Slots 36 / 37 (CSV DamageMgr::m36 / m37): the attacker links of the attack info the damage kind refers to
    // (`_d8` / `_e8`; kind 3: the first attack info's `_50`; kind 4 / 11: the actor's impulse link) or the dummy link.
    ksys::act::BaseProcLink* getAttacker() override;
    ksys::act::BaseProcLink* m37() override;
    // Slot 22 (CSV DamageMgr::m22, 0x71006d2a84): base periodic update, tail-called by
    // DamageMgrPlayer::m22 after the _22c timer handling below. Declared only.
    void m22() override;
    // The new virtual slots 50-56 (placeholders; m52 / m53 are constants).
    // Slot 50 returns bool (DamageManager::m50 (0x71006d6c30) and DamageMgrPlayer::m50
    // both produce 0/1 in w0); the old void declaration was a guess.
    // Slot 50 (0x71006d6c30) fills the damage values like sub_71006D33FC (the arguments of addDamage).
    virtual bool m50(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40);
    // 2026-10-07: slot 51 tests the lightning factor and the linked actor's name.
    virtual bool m51(const ksys::act::BaseProcLink* link);
    virtual s32 m52() { return 40; }
    virtual s32 m53() { return 0; }
    // Slots 54 / 55 (0x71006d8a54 / 0x71006d8be4; not decompiled): the condition damages of kind 2 / 4 (see m45).
    virtual void m54(const ConditionDamageInfo& info);
    virtual void m55(const ConditionDamageInfo& info);
    // Slot 56 (lane4 s50): returns bool (the result of DynamicActor::m154).
    virtual bool m56();

    // 0x71006d69f8 (not decompiled): the rigid body hit by the current damage (by damage kind
    // _5c: 2 / 6 via sub_71007A255C, 4 via the actor's +0x708 object), or null.
    ksys::phys::RigidBody* sub_71006D69F8();

    // 0x71006d7fb0 (lane4 s48; placeholder name): the reaction code (10 freeze, 9 burn, 6 / 11 electric, -1 none) the
    // attacker link of `info` (_e8) causes on this actor, from the attacker's element state and the damage param.
    s32 sub_71006D7FB0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);
    // 0x71006d6d88 (placeholder name): the reaction code of the attack type flags of `info` (0x800: sub_71006D7FB0),
    // -1 for none.
    s32 sub_71006D6D88(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);
    // 0x71006d6ec0 (placeholder name): whether the attack info `info` can hit this actor (not while DynamicActor slot
    // 151 has bit 3 or 4; flag 0x80000000 needs a player with Daruk's protection; not with flag 8; bit 0 or 1 of _18).
    bool sub_71006D6EC0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);
    // 0x71006d27bc / 0x71006d81d8 (lane4 s48; placeholder names): sets the maximum impulse of the main body / character
    // controller to `_80` times the first non-negative impulse threshold of the actor's damage param (-1 if none),
    // unless the param has IsCommonCalcImpuleDamage; the second one first stores `value` in `_80`.
    void sub_71006D27BC();
    void sub_71006D32F8();
    void sub_71006D81D8(f32 value);
    // 0x71006d357c (CSV DamageMgr::m22_x_0; placeholder name): applies one damage of kind `type` (callbacks of event
    // `eventId` first, then addDamage); records the kind, the flag `flag` (bit 1 of _216) and the ride flag (_8c).
    // 0x71006d33fc (CSV DamageMgr::m22_x; placeholder name): the damage values (the arguments of addDamage) of a
    // lightning hit (LightningAffect with _78 < 1 and Actor::m50), of m50, or of a gust (GustAffect and the wind flag
    // of the actor's Chemical).
    bool sub_71006D33FC(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40);
    // 0x71006d276c (was DamageMgrPlayer::x; in the DamageManager TU, inlined into resetDamage; called by
    // DamageMgrPlayer::applyDamage and PlayerNormal::enter_): resets the damage indices, flags and direction.
    // Placeholder name.
    void sub_71006D276C();
    // 0x71006d888c (placeholder name): condition damage of kind 3 (m45).
    void sub_71006D888C(const ConditionDamageInfo& info);
    bool sub_71006D357C(s32 type, s32 eventId, bool flag, s32 damage, s32 df48, u32 minDmg, u32 f50, s32 f54,
                        s32 f40);
    // 0x71006d8130 (lane4 s48; placeholder name): `_f8` of the attack info index `_6c` for damage kinds 2 / 10 / 6 (6 needs
    // bit 8 of `_216`), -1 otherwise.
    s32 sub_71006D8130();

    // 0x71006d8de8 (lane3 s36; declared only): the damage factor (1.0; 2.0 if the attacker's weapon is a
    // Pikohan / one-hit obliterator). Placeholder name.
    f32 sub_71006D8DE8();

    // 0x71006d8534 (lane1 s22): `_220 ? _220->_10 : 0`. Placeholder name.
    s32 sub_71006D8534() const;
    // 0x71006d8304 / 0x71006d8340 / 0x71006d837c (lane4 s47; placeholder names): fields 0x0 / 0x14 / 0x10 of the most
    // recent damage record.
    s32 sub_71006D8304() const;
    s32 sub_71006D8340() const;
    s32 sub_71006D837C() const;
    // 0x71006ee2b0 (in the ragdoll TU; called by DynamicActor::sub_71006DD21C): true for damage types 1, 4, 5 and 6,
    // else whether `_218` has bit 4 or 5 set. Placeholder name.
    bool sub_71006EE2B0() const;
    // 0x71006d82d4: `_219` is set and there are damage records.
    bool sub_71006D82D4() const;
    // 0x71006d83b8: whether bit `bit` of field 0x18 of the most recent damage record is set.
    bool sub_71006D83B8(s32 bit) const;

    s32 _68 = 0;  // WolfLinkRoot::enter_
    s32 _6c = -1;  // read by PreyRoot's damage callback (lane2 s42)
    s32 _70 = 0;  // current shield guard power (PlayerOrEnemy::m160)
    // A damage factor (ctor: 1.0; Horse::loadReduceAncientEnemyDamageInfo copies a status effect value).
    f32 _74 = 1.0f;
    // 0x71006d77b8 loads this as a float before testing against 1.0.
    f32 _78 = 0.0f;
    u32 _7c = 0;
    f32 _80 = 1.0f;  // multiplier of the impulse threshold (sub_71006D27BC)
    f32 _84;  // DynamicActor::m148 result (0x71006d32f8).
    s32 _88 = -1;  // attack info index of damage kind 6 (DamageManager::getAttackInfo_)
    s32 _8c = 0;  // WeakPointRoot::m35
    sead::Vector3f _90{0, 0, 0};  // position of damage kind 9 (getPosition)
    sead::Vector3f _9c = sead::Vector3f::ez;  // direction of damage kind 9 (getAttackPos)
    sead::Vector3f _a8 = sead::Vector3f::ez;  // direction of damage kind 9 (m31)
    sead::Vector3f _b4{0, 0, 0};  // blow of damage kind 9 (m32)
    sead::Vector3f _c0 = sead::Vector3f::zero;  // direction of damage kind 1 (getAttackPos)
    sead::Vector3f _cc = sead::Vector3f::zero;  // direction used by damage kind 7 (m29 / m30)
    // Message senders and listeners (DamageManager ctor 0x71006d23e0 and D1 0x71006d9130).
    Unk_710244e030 _d8;
    Unk_7102450af8 _f0;
    Unk_710244e058 _128;
    Unk_7102450b28 _140;
    Unk_7102358df0 _178;
    Unk_7102358dc0 _1a8;
    Unk_71023cee50 _1f8;
    // 0x210-0x22c: zeroed by the ctor (0x210 and 0x214 with one 8-byte store).
    u16 _210 = 0;
    u16 _212 = 0;
    u16 _214 = 0;
    // Flags (ctor: 9). AI code tests bit 1 (`_216.isOn(2)`, ~15 functions).
    sead::BitFlag16 _216;
    u8 _218 = 0;
    bool _219 = false;
    DamageManagerUnk220* _220 = nullptr;
    u32 _228 = 0;

private:
    // Inline-only in the original (name is a guess; evidence: m39 / m40 / m41 and the other overrides start with
    // it): the attack info the current damage kind (6: index _88 if bit 8 of _216 is set, 2: index _6c) refers to.
    ksys::act::ActorAtk::Unk_710079e64c::Unk1* getAttackInfo_();
};
KSYS_CHECK_SIZE_NX150(DamageManager, 0x230);

}  // namespace uking::dmg

namespace uking::dmg {
// 0x71006d7038 (placeholder name): whether `actor` (with the SleepSilentKill or AwakeSilentKill AttClient) takes a
// silent kill from the attack info `info` (flag 0x80000; its attacker link _d8 tested by 0x7100735ba8 / 0x7100735d2c).
bool sub_71006D7038(ksys::act::Actor* actor, ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);
}  // namespace uking::dmg

// 0x71006d28ac: actor attack info or a non-dummy damage resource requires a damage manager.
// Declaration only; namespace unknown.
bool sub_71006D28AC(ksys::act::Actor* actor);
// CSV name at 0x71006d28fc; declaration only, namespace unknown. Original allocates 0x230
// and calls DamageManager's actual 0x71006d23e0 constructor, returning that object or null.
uking::dmg::DamageManager* gameObjectInitField(ksys::act::Actor* actor, sead::Heap* heap);
