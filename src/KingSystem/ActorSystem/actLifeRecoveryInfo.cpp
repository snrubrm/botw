#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Utils/Thread/Message.h"

namespace ksys::act {

LifeRecoverInfo::LifeRecoverInfo() : mTimer(0, 0), mTimer2(0, 0) {}

// NON_MATCHING: the parameter's enabled byte is loaded after the enum temporary is initialized.
bool LifeRecoverInfo::init(const LifeRecoverParams* params) {
    mExtraHp1 = sead::Mathf::min(f32(mExtraHp2), 0.0f);
    mExtraHp2 = params->_0;
    mMaxLife = params->_4;
    mRecoverFactor = params->_8;
    mField_28 = params->_c;
    mField_2C = params->_10;
    const Flag enabled(0);
    if (params->_14)
        mFlags |= 1 << int(enabled);
    else
        mFlags &= ~(1 << int(enabled));
    mTimer.value = mTimer.previous_value = mField_28;
    const Flag recovered(1);
    mFlags &= ~(1 << int(recovered));
    return true;
}

// NON_MATCHING: init() inlined; same difference as init (the enabled byte is loaded after the enum temporary).
bool LifeRecoverInfo::sub_7100D68E54(const ksys::Message* message) {
    auto* params = static_cast<const LifeRecoverParams*>(message->getUserData());
    return params && init(params);
}

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

void LifeRecoverInfo::sub_7100D68D54() {
    mExtraHp1 = sead::Mathf::min(f32(mExtraHp2), 0.0f);
    const Flag enabled(0);
    mFlags &= ~(1 << int(enabled));
}

void LifeRecoverInfo::sub_7100D68AD4() {
    mExtraHp1 = sead::Mathf::min(f32(mExtraHp2), 0.0f);
    const Flag first(1);
    mFlags &= ~(1 << int(first));
    mTimer.value = mField_2C;
    mTimer.previous_value = mField_2C;
    const Flag second(1);
    mFlags &= ~(1 << int(second));
}

void LifeRecoverInfo::onApplyDamage_0() {
    mTimer.value = mField_2C;
    mTimer.previous_value = mField_2C;
    const Flag flag(1);
    mFlags &= ~(1 << int(flag));
}

}  // namespace ksys::act
