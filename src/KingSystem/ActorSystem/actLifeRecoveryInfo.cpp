#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>

namespace ksys::act {

bool LifeRecoverInfo::onApplyDamage(s32& damage) {
    const s32 extra = mExtraHp1;
    const s32 value = damage;
    if (extra == 0)
        return value > 0;
    const s32 remaining = std::max(extra - value, 0);
    damage = (value - extra) + remaining;
    mExtraHp1 = sead::Mathf::clampMax(f32(remaining), f32(mExtraHp2));
    return remaining != extra;
}

void LifeRecoverInfo::onApplyDamage_0() {
    mCounter = mField_2C;
    mField_4 = mField_2C;
    const Flag flag(1);
    mFlags &= ~(1 << int(flag));
}

}  // namespace ksys::act
