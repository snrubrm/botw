#pragma once
#include <container/seadObjArray.h>
#include <prim/seadEnum.h>
#include <xlink2/xlink2Locator.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Sound/sndUnk_7102502138.h"
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

private:
    sead::FixedObjArray<xlink2::Locator, 4> mSpeedLocators;
    sead::FixedObjArray<xlink2::Locator, 4> mStrengthLocators;
    bool mInitialized = false;
};

extern Unk_710251b170 sEquipmentNoiseCache;
KSYS_CHECK_SIZE_NX150(Unk_710251b170, 0x150);

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
    void m4(void* arg) override;
    void m5(void* arg) override;
    // 0x71012c45b0
    void m6() override;

    // 0x71012c3bc8 (declared only): searches the equipment noise locator of `name` in the player's SLink user.
    bool sub_71012C3BC8(const sead::SafeString& name);

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
    void m4(void* arg) override;
    void m5(void* arg) override;
    // 0x71012c4ff4: forgets the locators.
    void m6() override;

    // 0x71012c5034: the level (0, 1 or 2) of `value`.
    void sub_71012C5034(s32 value);

    /* 0x10 */ s32 _10 = 0;
    /* 0x18 */ sead::FixedObjArray<xlink2::Locator, 3> mLocators;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b128, 0x98);

}  // namespace ksys::snd
