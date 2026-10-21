#pragma once
#include <container/seadObjArray.h>
#include <prim/seadEnum.h>
#include <xlink2/xlink2Locator.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {
// Vtable 0x710251b170; global 0x710265fd38, initialized at 0x71012c5748.
class Unk_710251b170 {
public:
    SEAD_ENUM(Strength, Minimum,Weak,Middle,Strong)
    SEAD_ENUM(Speed, Dash,Fast,MdlSpd,Slow)
    virtual ~Unk_710251b170();
    void sub_71012C3074();
    bool isInitialized() const { return mInitialized; }

    // inline-only in the original; name is a guess (0x71012c3e94 and the other m4 overrides repeat it): the
    // locator of `speed`, loading the locators first if needed.
    xlink2::Locator* getSpeedLocator(const Speed& speed) {
        if (!mInitialized) {
            sub_71012C3074();
            if (!mInitialized)
                return nullptr;
        }
        return mSpeedLocators.at(speed);
    }

    // inline-only in the original; name is a guess (0x71012c43b0 and the other m5 overrides repeat it): the
    // locator of `strength`, loading the locators first if needed.
    xlink2::Locator* getStrengthLocator(const Strength& strength) {
        if (!mInitialized) {
            sub_71012C3074();
            if (!mInitialized)
                return nullptr;
        }
        return mStrengthLocators.at(strength);
    }

private:
    sead::FixedObjArray<xlink2::Locator, 4> mSpeedLocators;
    sead::FixedObjArray<xlink2::Locator, 4> mStrengthLocators;
    bool mInitialized = false;
};

extern Unk_710251b170 sEquipmentNoiseCache;

// 0x710251b018: the chance of the delayed variant of a step noise (and two factors used by 0x71012c4bbc).
struct Unk_710251b018 {
    f32 delayChance;
    f32 _4;
    f32 _8;
};
extern Unk_710251b018 sUnk_710251b018;
KSYS_CHECK_SIZE_NX150(Unk_710251b170, 0x150);

// Placeholder type named after its method at 0x71012c5034 (now a method of the subclass Unk_710251b128). The base
// of the equipment sound objects of Unk68 (Unk_710251b028 for the parts, Unk_710251b128 for the quiver); see
// sndEquipmentNoiseCache.h. No vtable of its own is used (both subclasses override every slot).
class Unk_71012C5034 {
public:
    virtual ~Unk_71012C5034() = default;
    // Called with a part name (Unk68::sub_710104DD20 passes "BaseEquip_Quiver").
    virtual bool m2(const sead::SafeString& name) = 0;
    virtual bool m3() = 0;
    virtual void m4(const Unk_710251b170::Speed* speed) = 0;
    virtual void m5(const Unk_710251b170::Strength* strength) = 0;
    virtual void m6() = 0;

    // 0x71012c384c (placeholder name): _c = m2(name), _d = !_c.
    void sub_71012C384C(const sead::SafeString& name);
    // 0x71012c3888 / 0x71012c38f8 (placeholder names): if _d is set, first _c = m3() (clearing _d); then m4 / m5
    // while _c is set.
    void sub_71012C3888(const Unk_710251b170::Speed* speed);
    void sub_71012C38F8(const Unk_710251b170::Strength* strength);
    // 0x71012c3968 (placeholder name): m6(), then clears _c and _d.
    void sub_71012C3968();

    s32 _8 = 0;
    bool _c = false;
    bool _d = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71012C5034, 0x10);


// Vtable 0x710251b028 (0x78 bytes; created by Unk68's constructor 0x710104bcbc for the equipment parts): plays the
// equipment noise of one part (the locator found from the part name).
class Unk_710251b028 : public Unk_71012C5034 {
public:
    Unk_710251b028();
    // 0x71012c3a54
    ~Unk_710251b028() override;

    // 0x71012c3a6c (declared only)
    bool m2(const sead::SafeString& name) override;
    // 0x71012c3e8c
    bool m3() override;
    // 0x71012c3e94 / 0x71012c43b0 (declared only)
    void m4(const Unk_710251b170::Speed* speed) override;
    void m5(const Unk_710251b170::Strength* strength) override;
    // 0x71012c45b0
    void m6() override;

    // 0x71012c3bc8 (declared only): searches the equipment noise locator of `name` in the player's SLink user.
    bool sub_71012C3BC8(const sead::SafeString& name);
    // 0x71012c3fc8: picks the next of three variants at random and writes the asset name for `speed`.
    void sub_71012C3FC8(sead::BufferedSafeString* out, const Unk_710251b170::Speed* speed);
    // 0x71012c40c8 (declared only): plays the asset of `locator` with the delay and the asset name.
    void sub_71012C40C8(const xlink2::Locator* locator, f32 delay, const sead::SafeString& name);
    // 0x71012c44a0: picks the next of three variants at random and writes the asset name for `strength`.
    void sub_71012C44A0(sead::BufferedSafeString* out, const Unk_710251b170::Strength* strength);

    /* 0x10 */ sead::FixedSafeString<48> mName;
    /* 0x58 */ xlink2::Locator mLocator;
    /* 0x70 */ bool _70 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b028, 0x78);

// Vtable 0x710251b128 (0x98 bytes; Unk68::_480): the quiver noise, with up to three locators.
class Unk_710251b128 : public Unk_71012C5034 {
public:
    Unk_710251b128();
    // 0x71012c5050
    ~Unk_710251b128() override = default;

    // 0x71012c4630 (declared only)
    bool m2(const sead::SafeString& name) override;
    // 0x71012c49e4: m2 with an empty name.
    bool m3() override;
    // 0x71012c4a2c / 0x71012c4eb0 (declared only)
    void m4(const Unk_710251b170::Speed* speed) override;
    void m5(const Unk_710251b170::Strength* strength) override;
    // 0x71012c4ff4: forgets the locators.
    void m6() override;

    // 0x71012c5034: the level (0, 1 or 2) of `value`.
    void sub_71012C5034(s32 value);

    /* 0x10 */ s32 _10 = 0;
    /* 0x18 */ sead::FixedObjArray<xlink2::Locator, 3> mLocators;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b128, 0x98);

}  // namespace ksys::snd
