#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>

#include "KingSystem/System/Timer.h"
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
    LifeRecoverInfo();
    bool init(const LifeRecoverParams* params);

    // Modifies extra Hp1 and Damage. (Regen?)
    bool onApplyDamage(s32& damage);

    // Update flags and counter
    void onApplyDamage_0();

    void printLifeRecoverInfo(u32 life, sead::FormatFixedSafeString<128>** Output);

    // SEAD_ENUM in the original (stack round trip): bit index of the flag cleared by onApplyDamage_0.
    SEAD_ENUM(Flag, _0, _1)

    // D68B5C updates both timers through Timer::update.
    Timer mTimer;
    Timer mTimer2;
    s32 mExtraHp1 = 0;
    s32 mExtraHp2 = 0;
    s32 mMaxLife = 0;
    f32 mRecoverFactor = 0;
    f32 mField_28 = 0;
    f32 mField_2C = 0;
    u8 mFlags = 0;
    u8 mUnknown[7];  // Flags might just be two u32
};
KSYS_CHECK_SIZE_NX150(LifeRecoverInfo, 0x38);

}  // namespace ksys::act
