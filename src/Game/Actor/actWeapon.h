#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem//ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorConstDataAccess;
class InstParamPack;
namespace ai {
struct InlineParamPack;
}
}  // namespace ksys::act

namespace ksys::evt {
class OrderParam;
}

namespace ksys::res {
class GParamList;
}

namespace uking::ui {
class PouchItem;
}

namespace uking::act {

enum class WeaponModifier : u32 {
    None = 0,
    /// Attack Up (swords and bows)
    AddAtk = 0x1,
    /// Durability Up
    AddLife = 0x2,

    /// Critical Hit (swords)
    AddCrit = 0x4,
    /// Long Throw (swords)
    AddThrow = 0x8,

    /// Multi-shot (bows)
    AddSpreadFire = 0x10,
    /// ??? (bows)
    AddZoomRapid = 0x20,
    /// Quick Shot (bows)
    AddRapidFire = 0x40,

    /// Unused bonus type (shields)
    AddSurfMaster = 0x80,
    /// Shield Guard Up (shields)
    AddGuard = 0x100,

    /// Whether this is a yellow tier (PoweredSharp) modifier.
    IsYellow = 0x80000000,
};

struct WeaponModifierRanges;

struct WeaponModifierInfo {
    WeaponModifierInfo() : value() {}
    explicit WeaponModifierInfo(const ui::PouchItem& item);
    void fromItem(const ui::PouchItem& item);

    int getAddLife() const;
    static int getLifeMultiplier();

    void loadPorchSwordFlag(int idx);
    void loadPorchShieldFlag(int idx);
    void loadPorchBowFlag(int idx);

    void savePorchSwordFlag(int idx) const;
    void savePorchShieldFlag(int idx) const;
    void savePorchBowFlag(int idx) const;

    void loadEquipStandSwordFlag(int idx);
    void loadEquipStandShieldFlag(int idx);
    void loadEquipStandBowFlag(int idx);

    void saveEquipStandSwordFlag(int idx) const;
    void saveEquipStandShieldFlag(int idx) const;
    void saveEquipStandBowFlag(int idx) const;

    void addModifierParams(ksys::act::InstParamPack& params) const;
    void set(u32 type_, u32 value_);
    static void addModifierParams(WeaponModifierInfo* self, ksys::evt::OrderParam& params);
    static void addModifierParams(WeaponModifierInfo* self, ksys::act::ai::InlineParamPack& params);

    bool pickRandomBlueModifierAmiibo(const sead::SafeString& actor);
    bool pickRandomYellowModifierAmiibo(const sead::SafeString& actor);
    bool pickRandomModifierAmiibo(const WeaponModifierRanges& ranges);

    bool pickRandomModifier(const WeaponModifierRanges& ranges);

    bool pickRandomBlueModifierTbox(const sead::SafeString& actor);
    bool pickRandomYellowModifierTbox(const sead::SafeString& actor);

    bool pickRandomBlueModifierActor(const ksys::act::ActorConstDataAccess& acc);
    bool pickRandomYellowModifierActor(const ksys::act::ActorConstDataAccess& acc);

    void setModifier(WeaponModifier modifier, s32 value_) {
        flags.setDirect((flags.getDirect() & u32(WeaponModifier::IsYellow)) | u32(modifier));
        value = value_;
    }

    void setModifierFloat(WeaponModifier modifier, f32 value_) {
        flags.setDirect((flags.getDirect() & u32(WeaponModifier::IsYellow)) | u32(modifier));
        value = value_ * 1000.0f;
    }

    sead::TypedBitFlag<WeaponModifier> flags;
    s32 value;
};

struct WeaponModifierRanges {
    bool loadTierBlue(const sead::SafeString& actor);
    bool loadTierYellow(const sead::SafeString& actor);

    bool loadTierBlue(const ksys::res::GParamList& gparamlist);
    bool loadTierYellow(const ksys::res::GParamList& gparamlist);

    WeaponModifier getRandomModifier() const;
    bool isConfigValid() const;

    int addAtkMin = 0;
    int addAtkMax = 0;
    int addLifeMin = 0;
    int addLifeMax = 0;
    bool addCrit = false;
    int addGuardMin = 0;
    int addGuardMax = 0;
    float addThrowMin = 1.0;
    float addThrowMax = 1.0;
    bool addSpreadFire = false;
    bool addZoomRapid = false;
    float addRapidFireMin = 1.0;
    float addRapidFireMax = 1.0;
    bool addSurfMaster = false;
    bool isTierYellow = false;
};

// Request passed to Weapon::sub_71002EDA38 (stored at Weapon+0xaf8 under the lock at 0xab8; the
// flag at 0xb40 marks it as pending). Built by AI helpers (0x71005d80fc: type 6, 0x71005d8210:
// type 7) and passed down via PlayerOrEnemy / NPC (0x71005d787c). Placeholder name and fields.
struct Unk_71002eda38 {
    Unk_71002eda38() = default;
    explicit Unk_71002eda38(s32 type) { _0 = type; }

    /* 0x00 */ s32 _0 = -1;
    /* 0x04 */ s32 _4 = 0;
    /* 0x08 */ sead::Vector3f _8 = {0, 0, 0};
    /* 0x14 */ sead::Vector3f _14 = {0, 0, 0};
    /* 0x20 */ ksys::act::BaseProcLink _20;
    /* 0x30 */ f32 _30 = 1.0;
    /* 0x34 */ f32 _34 = 1.0;
    /* 0x38 */ s32 _38 = -1;
    /* 0x3c */ bool _3c = false;
    /* 0x40 */ u64 _40 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71002eda38, 0x48);

// Request passed to Weapon::sub_71002EDAEC (stored at Weapon+0xc20 under the lock at 0xbe0; flag at
// 0xc4c). Passed down via PlayerOrEnemy / NPC (0x71005d79ac). Placeholder name and fields.
// Placeholder name (0x71002ef75c): the object Weapon::_d38 points to (EquipedDeadlyBlowWeapon::handleMessage_ and
// EquipedChemicalWeapon::calc_ call its method); its first member is the owner actor. Opaque so far.
class Weapon;

struct Unk_71002ef75c {
    // Placeholder: the object at `_8` (only two s32 fields are known).
    struct Unk1 {
        u8 _0[0x2a8];
        /* 0x2a8 */ s32 _2a8;  // charge decrement of sub_71002EF850 / the maximum charge
        u8 _2ac[0x2c8 - 0x2ac];
        /* 0x2c8 */ s32 _2c8;  // charge decrement of sub_71002EF75C (not charging)
    };

    // 0x71002ef75c: decreases the charge `_14` (by `_8->_2c8`, or while charging by the current maximum
    // charge / 13 (or `_14`)) and sets the flag 1 of _18 when it reaches 0. Names are guesses.
    void sub_71002EF75C();

    // 0x71002e999c: the part of Weapon::m214 after the `_18` check (lane4 s46; placeholder name).
    bool sub_71002E999C();

    // 0x71002ef850: `_14 -= (f32)_8->_2a8; if (_14 <= 0) { _18 |= 1; _14 = 0; }`.
    void sub_71002EF850();
    // 0x71002ef74c: the maximum charge: `(f32)_8->_2a8`.
    f32 sub_71002EF74C();

    // Layout from ChemicalWeaponRoot::calc_ / sub_7100348B18 (lane1 s28); everything else is unknown.
    /* 0x00 */ Weapon* _0;  // owner
    /* 0x08 */ Unk1* _8;
    /* 0x10 */ u32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ u8 _18;  // flags (bit 0: charge used up; bit 3 starts the "ChemSwordChargeLoop" xlink)
};

// Request passed to Weapon::sub_71002EDC14 (stored at Weapon+0xcd8 under the lock at 0xc98; flag at 0xce0).
// Placeholder name and fields (lane4 s46).
struct Unk_71002edc14 {
    /* 0x0 */ u32 _0 = 0;
    /* 0x4 */ u8 _4 = 0;
};

struct Unk_71002edaec {
    Unk_71002edaec() = default;
    explicit Unk_71002edaec(s32 type) { _0 = type; }

    /* 0x00 */ s32 _0 = -1;
    /* 0x04 */ s32 _4 = 0;
    /* 0x08 */ f32 _8 = 1.0;
    /* 0x0c */ f32 _c = 1.0;
    /* 0x10 */ s32 _10 = -1;
    /* 0x14 */ u8 _14 = 0;  // flags (bit 3 is read by ChemicalWeaponRoot / DeadlyBlowWeaponRoot::m42: lane1 request)
    /* 0x18 */ s32 _18 = 1;
    /* 0x1c */ s32 _1c = 1;
    /* 0x20 */ s32 _20 = 0;
    /* 0x24 */ s32 _24 = 1;
    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71002edaec, 0x2c);

// TODO: Weapon class (factory 0x71002df038: new(0x1038); ctor 0x71002e04ac). Only the start of
// the layout is declared.
class Weapon : public ksys::act::WeaponBase {
    SEAD_RTTI_OVERRIDE(Weapon, ksys::act::WeaponBase)
public:
    // 0x71002e5f88 (CSV Weapon::m175): `x_4(pos, false, false, a4, false)`, then the base.
    bool m175(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) override;
    // 0x71002ee7e8 (lane1 s41, declaration only; placeholder name): writes the enemy actor link that is both the
    // player's attention target and the weapon's `_b18` (or `_b18` itself) to `out`; false if there is none.
    bool sub_71002EE7E8(ksys::act::BaseProcLink* out);
    // 0x71002e5ddc (lane3 s36; declared only; 260 B): a direction in the weapon's local space, read from its
    // main body (RTTI-checked). Placeholder name.
    void sub_71002E5DDC(sead::Vector3f* out);
    // 0x71002edc64 (CSV Weapon::x_6): `return hasAttackInfo(this)` (a tail call).
    bool x_6();
    // 0x71002e4374: bit7 of _e50, or a type3 weapon with a connected calc child.
    bool sub_71002E4374();
    s32 getShieldGuardPower();
    f32 getShieldSurfingFriction();
    s32 getAttackPower();
    bool isThrowingBreakWeapon();
    bool bowHasArrowName();
    // Bow modifier helpers (placeholder names, lane4 s45). The bow param's IsLeadShot / LeadShotNum /
    // IsRapidFire / RapidFireNum, overridden by the AddSpreadFire / AddZoomRapid modifiers.
    bool sub_71002EA0D4();
    s32 sub_71002EA124();
    bool sub_71002EA16C();
    s32 sub_71002EA1A8();
    // 0x71002ea21c / 0x71002ea244: the bow param's ExtraDamageRatio / BaseAttackPowerRatio.
    f32 sub_71002EA21C();
    f32 sub_71002EA244();
    // 0x71002ee484 .. 0x71002ee594: the bow param's IsGuardPierce, ArrowFirstSpeed, ArrowAcceleration,
    // ArrowStabilitySpeed, ArrowGravity / 900, ArrowFallAcceleration, ArrowFallStabilitySpeed.
    bool sub_71002EE484();
    f32 sub_71002EE4C0();
    f32 sub_71002EE4E8();
    f32 sub_71002EE510();
    f32 sub_71002EE538();
    f32 sub_71002EE56C();
    f32 sub_71002EE594();
    // 0x71002ed8a0: WeaponCommon's IsThrowingWeapon (false without the param).
    bool sub_71002ED8A0();
    // 0x71002ed934 / 0x71002ed9b0 (placeholder names): for a master sword, whether the parent actor's life is at its
    // maximum / the parent's life (at least 4), as float. 0 / false otherwise.
    bool sub_71002ED934();
    f32 sub_71002ED9B0();
    // 0x71002ed8dc: WeaponThrow's ThrowDist, scaled by the AddThrow modifier.
    f32 sub_71002ED8DC();
    s32 getMaxHp();
    s32* getLife() override;
    ksys::act::Unk_71025ae640* getAtk() override;
    ksys::act::Unk_71025ae620* getDropData() override;
    ksys::act::Actor::Unk3* m135() override;
    ksys::act::Unk_71025b08f8* m126() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;
    ksys::act::Unk_71006e45c4* m128() override;
    bool m137() override;
    bool m138() override;
    f32 m139() override;
    bool m195() override;
    bool x_0();
    bool isParentPlayer() override;
    bool isParentNpc() override;
    bool m142() override;
    bool m183() override;
    bool m184() override;
    // 0x71002e5ff0 (CSV Weapon::x_4; not decompiled): resets the weapon's effects (damage colour etc.);
    // `a4` is DynamicCast to the class with RTTI 0x71025b1538 (copies the parent link and two flags).
    void x_4(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    // 0x71002e9a50 (lane1 s21): the chemical's state is 2 (false without a chemical).
    bool sub_71002E9A50();
    // 0x71002e38ec (CSV Weapon::isTrueFormMasterSword): a master sword (vslot 219) while
    // the DamageInfoMgr says it is in its true form.
    bool isTrueFormMasterSword();
    bool isMasterSword() override;
    bool isBoomerang() override;
    bool isWeaponType0Or1Or2() const override;
    bool isWeaponType4() const override;
    bool isWeaponType3() const override;
    bool m173(s32 index, ksys::act::Actor* actor, const char* name, const char* other_name,
              bool a5, bool a6) override;
    bool m174() override;
    bool m176(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4, void* a5,
              bool a6) override;
    bool m177(const sead::Vector3f& target, void* a2) override;
    bool m178(const sead::Vector3f& pos) override;
    void m181() override;
    bool m204() override;
    bool m205() override;
    void m215() override;
    void* m221() override;
    bool m222() override;
    bool m194() override;
    void masterSwordReturnToForest() override;
    bool m227() override;
    void m228(ksys::act::BaseProc* proc) override;
    void m229(ksys::act::BaseProc* proc) override;
    void updateLifeMaybe(ksys::act::BaseProc* proc);
    void m249(sead::Matrix34f* matrix, ksys::act::Actor* actor) override;
    bool m250(ksys::act::Actor* actor) override;
    bool m239() override;
    void m240(sead::Vector3f* out) override;
    void m241(sead::Vector3f* out) override;
    void m242(sead::Vector3f* out) override;
    void m243(sead::Vector3f* out) override;
    void m245(sead::Vector3f* out) override;
    void m246(sead::Vector3f* out) override;
    void m247(sead::Vector3f* out) override;
    void m248(sead::Vector3f* out) override;
    void invokedEmitBlinkEffect();
    bool m197(sead::SafeString* out) override;
    void updateMtxFromPhysics() override;
    bool m218() override;
    bool m225() override;
    bool m226() override;
    void m206(bool play_sound) override;
    bool m153() override;
    bool m155() override;
    bool m156() override;
    ksys::act::ActorWeapons* getParentActorWeapons();
    s32 getEffectiveAttackPower(ksys::act::Actor* actor);
    bool m216() override;
    bool m211() override;
    bool m212() override;
    bool m213() override;
    bool m214() override;
    bool m231() const override;
    bool m232() const override;
    bool m233() const override;
    // Declaration only: 0x71002ed434, queried by Player::m248.
    f32 sub_71002ED434();
    // Declaration only: 0x71002ed730, queried by PlayerOrEnemy::sub_7100007BF8 (lane4 s46).
    f32 sub_71002ED730(bool a1);
    // lane4 s46 (placeholder names, unnamed in the CSV). 0x71002ea0c8: has the (unnamed) tag 0xdf7c57f6.
    bool sub_71002EA0C8();
    // 0x71002edb84: `_bd0 = value; _bd8 = true` under the lock `_b90`.
    void sub_71002EDB84(const u64& value);
    // lane4 s46 (placeholder names; the callers pass a local holding 4): 0x71002ecafc: the Attack param Impulse
    // (ImpulseLarge if `flags` has bit 1 or 2). 0x71002ecb3c: GuardBreakPower (x1.5 with those bits).
    f32 sub_71002ECAFC(const sead::BitFlag8& flags);
    s32 sub_71002ECB3C(const sead::BitFlag8& flags);
    // lane4 s46 (placeholder names): 0x71002ed274 / 0x71002e9a7c test the chemical material attribute (bit 0 / both of
    // 0x88) and a flag of the chemical (_be bit 0 / bit 2).
    bool sub_71002ED274();
    bool sub_71002E9A7C();
    // 0x71002edbcc: `_c90 = value; _c94 = true` under the lock `_c50`.
    void sub_71002EDBCC(const u32& value);
    // 0x71002edc14: `_cd8 = value; _ce0 = true` under the lock `_c98`.
    void sub_71002EDC14(const Unk_71002edc14& value);
    void sub_71002EDA38(const Unk_71002eda38& arg);
    void sub_71002EDAEC(const Unk_71002edaec& arg);
    // 0x71002edb3c: stores `value` to _b88 (under _b48) and sets _b8c (behavior WeaponChemicalReset).
    SEAD_ENUM(Unk3, _0, _1, _2, _3)
    void sub_71002EDB3C(const Unk3& value);
    // 0x71002ee1f0: bow resource arrow name, or the owning player/enemy arrow name.
    bool bowGetArrowName(sead::BufferedSafeString* name);
    const sead::Vector3f* getAttackPosMaybe() const;

    /* 0xab8 */ sead::CriticalSection _ab8;
    /* 0xaf8 */ Unk_71002eda38 _af8;
    /* 0xb40 */ bool _b40 = false;
    /* 0xb48 */ sead::CriticalSection _b48;
    /* 0xb88 */ s32 _b88 = -1;
    /* 0xb8c */ bool _b8c = false;
    /* 0xb90 */ sead::CriticalSection _b90;
    /* 0xbd0 */ u64 _bd0 = 0;
    /* 0xbd8 */ bool _bd8 = false;
    /* 0xbe0 */ sead::CriticalSection _be0;
    /* 0xc20 */ Unk_71002edaec _c20;
    /* 0xc4c */ bool _c4c = false;
    /* 0xc4d */ u8 _c4d[0xc50 - 0xc4d];  // TODO
    /* 0xc50 */ sead::CriticalSection _c50;
    /* 0xc90 */ u32 _c90 = 0;
    /* 0xc94 */ bool _c94 = false;
    /* 0xc98 */ sead::CriticalSection _c98;
    /* 0xcd8 */ Unk_71002edc14 _cd8;
    /* 0xce0 */ bool _ce0 = false;
    /* 0xce1 */ u8 _ce1[0xcec - 0xce1];  // TODO
    /* 0xcec */ s32 _cec = -1;
    /* 0xcf0 */ s32 _cf0 = -1;  // flags (BitFlag32; the sign bit is tested by AI helpers); sub_71005DBB60 returns it
    /* 0xcf4 */ u8 _cf4[0xd08 - 0xcf4];  // TODO
    /* 0xd08 */ u8 _d08;  // read by ChemicalWeaponRoot / DeadlyBlowWeaponRoot::m42 (lane1 request)
    /* 0xd09 */ bool _d09;
    /* 0xd0a */ u8 _d0a[2];  // TODO
    /* 0xd0c */ s32 _d0c;  // read by Arrow::sub_710046ABA8 (lane1 s41)
    /* 0xd10 */ u8 _d10[0xd38 - 0xd10];  // TODO
    /* 0xd38 */ Unk_71002ef75c* _d38 = nullptr;
    /* 0xd40 */ u8 _d40[0xd4c - 0xd40];  // TODO
    // The signed life value returned by getLife; the original constructor initializes it to zero.
    /* 0xd4c */ s32 mLife;
    /* 0xd50 */ u8 _d50[0xd54 - 0xd50];  // TODO
    /* 0xd54 */ s32 _d54 = 0;
    /* 0xd58 */ u8 _d58[0xd64 - 0xd58];  // TODO
    /* 0xd64 */ f32 _d64;  // scale of the attack range (sub_71002ED434)
    /* 0xd68 */ ksys::phys::RigidBody* _d68 = nullptr;  // two pointers compared by WeaponThrowerSelector::enter_
    /* 0xd70 */ void* _d70 = nullptr;
    /* 0xd78 */ u8 _d78[0xd90 - 0xd78];  // TODO
    /* 0xd90 */ ksys::act::Unk_71006e45c4* _d90;
    /* 0xd98 */ ksys::act::Unk_71025b08f8* _d98;
    /* 0xda0 */ ksys::act::ActorAtk _da0{this};  // getAtk
    /* 0xe20 */ void* _e20 = nullptr;
    /* 0xe28 */ uking::dmg::DamageManagerBase* mDamageMgr;
    /* 0xe30 */ u8 _e30[0xe50 - 0xe30];  // TODO
    /* 0xe50 */ u16 _e50 = 0;  // flags (BowEquiped::leave_ uses 16-bit accesses)
    /* 0xe52 */ u16 _e52;
    /* 0xe54 */ u8 _e54[0xf58 - 0xe54];  // TODO
    /* 0xf58 */ bool _f58;
    /* 0xf59 */ u8 _f59[0xf60 - 0xf59];  // TODO
    /* 0xf60 */ ksys::act::BaseProcLink _f60;
    /* 0xf70 */ u8 _f70[3];
    /* 0xf73 */ bool _f73 = false;
    /* 0xf74 */ u8 _f74[0xf89 - 0xf74];
    /* 0xf89 */ bool _f89;  // cleared by ASWeaponRoot::enter_, set by its leave_
    u8 _f8a[0xf90 - 0xf8a];
    /* 0xf90 */ ksys::act::Unk_71025ae620* mDropData;
    /* 0xf98 */ WeaponModifierInfo _f98;
    /* 0xfa0 */ u8 _fa0[0xfb0 - 0xfa0];  // TODO
    /* 0xfb0 */ s32 _fb0;
    /* 0xfb4 */ u8 _fb4[0xfc8 - 0xfb4];  // TODO
    /* 0xfc8 */ bool _fc8;
    /* 0xfc9 */ u8 _fc9[0xfd0 - 0xfc9];  // TODO
    /* 0xfd0 */ ksys::phys::RigidBody* _fd0;
    /* 0xfd8 */ bool _fd8;
    /* 0xfd9 */ u8 _fd9[0x1008 - 0xfd9];  // TODO
    /* 0x1008 */ ksys::act::Actor::Unk3 _1008;
    /* 0x1010 */ u8 _1010[0x1014 - 0x1010];
    /* 0x1014 */ u8 _1014;
};

}  // namespace uking::act

namespace ksys::act::acc {

// Access to a uking::act::Weapon through an ActorConstDataAccess (CSV: act::acc::Weapon; functions
// 0x71002ef980-0x71002f13f0 in the Weapon TU). Namespace as for the other acc:: accessors.
// TODO: incomplete
class Weapon : public ActorConstDataAccess {
public:
    // 0x71002ef980: Weapon::hasParentActor() (false if not a weapon)
    bool sub_71002EF980() const;
    bool isShield() const;
    s32 getAttackPower() const;
    bool isHitEnemy() const;
    // 0x71002f1228: Actor::checkForbidAttentionSignal() (false if not a weapon)
    bool sub_71002F1228() const;

protected:
    uking::act::Weapon* getWeapon() const;
};
KSYS_CHECK_SIZE_NX150(Weapon, 0x18);

}  // namespace ksys::act::acc

// 0x71002edc68 / 0x71002edca8 (CSV names): guard bits of the actor's attack info zero, if present.
bool actorCheckIsGuard(ksys::act::Actor* actor);
bool actorCheckIsGuardJust(ksys::act::Actor* actor);

// Accessor-based wrappers in the Weapon TU (0x71002efa84-0x71002f1400). They cast the accessor's proc to a
// uking::act::Weapon (the default value without one) and read a GParam / member or forward to a virtual.
// Placeholder names (sub_<ADDR>) where the CSV has none.
namespace ksys::act {
bool getWeaponCommonIsPikohan(const ActorConstDataAccess& accessor);
s32 getShieldMirrorLevel(const ActorConstDataAccess& accessor);
}  // namespace ksys::act
// 0x71002efc98 / 0x71002efe08: WeaponCommon IsBlunt / IsWeakBreaker.
bool sub_71002EFC98(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71002EFE08(const ksys::act::ActorConstDataAccess& accessor);
// 0x71002efec0: a master sword whose parent has full life. 0x71002f000c: such a master sword's parent life (at least 4),
// 0 otherwise. 0x71002f034c: the Bow charge rate multiplied by the RapidFire modifier (1 without it or a weapon). 0x71002f0924: `_920 != 0xff || _921`.
bool sub_71002EFEC0(const ksys::act::ActorConstDataAccess& accessor);
f32 sub_71002F000C(const ksys::act::ActorConstDataAccess& accessor);
f32 sub_71002F034C(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71002F0924(const ksys::act::ActorConstDataAccess& accessor);
// 0x71002f0154: Weapon::m153. 0x71002f0258: `_cf0` (the weapon type), -1 without a weapon.
bool sub_71002F0154(const ksys::act::ActorConstDataAccess& accessor);
s32 sub_71002F0258(const ksys::act::ActorConstDataAccess& accessor);
// 0x71002f0de0: `_1014 < 5`. 0x71002f1400: `_cec = value`.
bool sub_71002F0DE0(const ksys::act::ActorConstDataAccess& accessor);
void sub_71002F1400(const ksys::act::ActorConstDataAccess& accessor, s32 value);
// 0x71002f1000: Weapon::m214. 0x71002f0ee0: Weapon::isTrueFormMasterSword.
bool sub_71002F1000(const ksys::act::ActorConstDataAccess& accessor);
// 0x71002f0cb4: Weapon::getShieldGuardPower (0 without a weapon). 0x71002f0490: the Bow reload rate divided by the RapidFire modifier (1 without a weapon).
// 0x71002f05d8: `&_f98` (the modifier info).
s32 sub_71002F0CB4(const ksys::act::ActorConstDataAccess& accessor);
f32 sub_71002F0490(const ksys::act::ActorConstDataAccess& accessor);
uking::act::WeaponModifierInfo* sub_71002F05D8(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71002F0EE0(const ksys::act::ActorConstDataAccess& accessor);
