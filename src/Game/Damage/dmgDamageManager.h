#pragma once

#include <container/seadRingBuffer.h>

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"
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

class DamageManager : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageManager, DamageManagerBase)
public:
    explicit DamageManager(ksys::act::Actor* actor);
    void preDelete1() override;
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
    // Slots 29 / 30 (CSV DamageMgr::m29 / m30): the normalised `_cc` for damage kind 7 when bit 6 of `_216` is set,
    // else the base class.
    bool m29(sead::Vector3f* out) override;
    bool m30(sead::Vector3f* out) override;
    // Slots 33 / 34 (CSV DamageMgr::m33 / m34): the material masks of the attack info (`_20` / `_38`) or null.
    ksys::phys::MaterialMask* m33() override;
    ksys::phys::MaterialMask* tgSensorMaterialOnHitMaybe() override;
    // Slots 36 / 37 (CSV DamageMgr::m36 / m37): the attacker links of the attack info the damage kind refers to
    // (`_d8` / `_e8`; kind 3: the first attack info's `_50`; kind 4 / 11: the actor's impulse link) or the dummy link.
    ksys::act::BaseProcLink* getAttacker() override;
    ksys::act::BaseProcLink* m37() override;
    // The new virtual slots 50-56 (placeholders; m52 / m53 are constants).
    virtual void m50();
    virtual void m51();
    virtual s32 m52() { return 40; }
    virtual s32 m53() { return 0; }
    virtual void m54();
    virtual void m55();
    // Slot 56 (lane4 s50): returns bool (the result of DynamicActor::m154).
    virtual bool m56();

    // 0x71006d69f8 (not decompiled): the rigid body hit by the current damage (by damage kind
    // _5c: 2 / 6 via sub_71007A255C, 4 via the actor's +0x708 object), or null.
    ksys::phys::RigidBody* sub_71006D69F8();

    // 0x71006d7fb0 (lane4 s48; placeholder name): the reaction code (10 freeze, 9 burn, 6 / 11 electric, -1 none) the
    // attacker link of `info` (_e8) causes on this actor, from the attacker's element state and the damage param.
    s32 sub_71006D7FB0(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);
    // 0x71006d27bc / 0x71006d81d8 (lane4 s48; placeholder names): sets the maximum impulse of the main body / character
    // controller to `_80` times the first non-negative impulse threshold of the actor's damage param (-1 if none),
    // unless the param has IsCommonCalcImpuleDamage; the second one first stores `value` in `_80`.
    void sub_71006D27BC();
    void sub_71006D81D8(f32 value);
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
    // 0x71006d82d4: `_219` is set and there are damage records.
    bool sub_71006D82D4() const;
    // 0x71006d83b8: whether bit `bit` of field 0x18 of the most recent damage record is set.
    bool sub_71006D83B8(s32 bit) const;

    s32 _68;  // WolfLinkRoot::enter_
    s32 _6c;  // read by PreyRoot's damage callback (lane2 s42)
    s32 _70;  // current shield guard power (PlayerOrEnemy::m160)
    s32 _74;  // Horse::loadReduceAncientEnemyDamageInfo
    u8 _78[0x80 - 0x78];
    f32 _80;  // multiplier of the impulse threshold (sub_71006D27BC)
    u8 _84[0x88 - 0x84];
    s32 _88;  // attack info index of damage kind 6 (DamageManager::getAttackInfo_)
    s32 _8c;  // WeakPointRoot::m35
    u8 _90[0xcc - 0x90];
    sead::Vector3f _cc;  // direction used by damage kind 7 (m29 / m30)
    u8 _d8[0x210 - 0xd8];
    // 0x210-0x22c: zeroed by the ctor (0x210 and 0x214 with one 8-byte store).
    u16 _210;
    u16 _212;
    u16 _214;
    // Flags (ctor: 9). AI code tests bit 1 (`_216.isOn(2)`, ~15 functions).
    sead::BitFlag16 _216;
    u8 _218;
    bool _219;
    DamageManagerUnk220* _220;
    u32 _228;

private:
    // Inline-only in the original (name is a guess; evidence: m39 / m40 / m41 and the other overrides start with
    // it): the attack info the current damage kind (6: index _88 if bit 8 of _216 is set, 2: index _6c) refers to.
    ksys::act::ActorAtk::Unk_710079e64c::Unk1* getAttackInfo_();
};
KSYS_CHECK_SIZE_NX150(DamageManager, 0x230);

}  // namespace uking::dmg

// 0x71006d28ac: actor attack info or a non-dummy damage resource requires a damage manager.
// Declaration only; namespace unknown.
bool sub_71006D28AC(ksys::act::Actor* actor);
// CSV name at 0x71006d28fc; declaration only, namespace unknown. Original allocates 0x230
// and calls DamageManager's actual 0x71006d23e0 constructor, returning that object or null.
uking::dmg::DamageManager* gameObjectInitField(ksys::act::Actor* actor, sead::Heap* heap);
