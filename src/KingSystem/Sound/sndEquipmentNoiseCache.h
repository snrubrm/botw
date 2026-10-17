#pragma once
#include <container/seadObjArray.h>
#include <prim/seadEnum.h>
#include <xlink2/xlink2Locator.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {
// Vtable 0x710251b170; global 0x710265fd38, initialized at 0x71012c5748.
class Unk_710251b170 {
public:
    SEAD_ENUM(Strength, Minimum,Weak,Middle,Strong)
    SEAD_ENUM(Speed, Dash,Fast,MdlSpd,Slow)
    virtual ~Unk_710251b170();
    void sub_71012C3074();

private:
    sead::FixedObjArray<xlink2::Locator, 4> mSpeedLocators;
    sead::FixedObjArray<xlink2::Locator, 4> mStrengthLocators;
    bool mInitialized = false;
};

extern Unk_710251b170 sEquipmentNoiseCache;
KSYS_CHECK_SIZE_NX150(Unk_710251b170, 0x150);
}
