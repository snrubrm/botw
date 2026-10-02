#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Parameters of LifeRecoverInfo::init (copied to _1c-_30), filled by getLifeRecoverParams.
// Field meanings unknown (getLifeRecoverParams: _0 and _4 are derived from Actor vtable slot 30,
// defaults _8 = 0.1, _c = 45, _10 = 90, _14 = true).
struct LifeRecoverParams {
    s32 _0;
    s32 _4;
    f32 _8;
    f32 _c;
    f32 _10;
    bool _14;
};
KSYS_CHECK_SIZE_NX150(LifeRecoverParams, 0x18);

// 0x7100d68598 (CSV name; namespace unknown): fills `params` for `actor` (values depend on the
// actor's tags and name).
void getLifeRecoverParams(LifeRecoverParams* params, Actor* actor);

// FIXME: incomplete
class LifeRecoverInfo {
public:
    void init(const LifeRecoverParams* params);

    // Modifies extra Hp1 and Damage. (Regen?)
    bool onApplyDamage(s32& damage);

    // Update flags and counter
    void onApplyDamage_0();

    void printLifeRecoverInfo(u32 life, sead::FormatFixedSafeString<128>** Output);

    f32 mCounter;
    f32 mField_4;
    u8 gap_8[16];  // Is this really a gap?
    u32 mExtraHp1;
    u32 mExtraHp2;
    u32 mMaxLife;
    f32 mRecoverFactor;
    s32 mField_28;
    f32 mField_2C;
    u8 mFlags;
    u8 mUnknown[7];  // Flags might just be two u32
};
KSYS_CHECK_SIZE_NX150(LifeRecoverInfo, 0x38);

}  // namespace ksys::act
