#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
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
struct Unk_71002edaec {
    /* 0x00 */ s32 _0 = -1;
    /* 0x04 */ s32 _4 = 0;
    /* 0x08 */ f32 _8 = 1.0;
    /* 0x0c */ f32 _c = 1.0;
    /* 0x10 */ s32 _10 = -1;
    /* 0x14 */ bool _14 = false;
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
    void sub_71002EDA38(const Unk_71002eda38& arg);
    void sub_71002EDAEC(const Unk_71002edaec& arg);

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
    /* 0xc50 */ u8 _c50[0xd54 - 0xc50];  // TODO
    /* 0xd54 */ s32 _d54 = 0;
    /* 0xd58 */ u8 _d58[0xe50 - 0xd58];  // TODO
    /* 0xe50 */ u8 _e50 = 0;  // flags
};

}  // namespace uking::act
