#include "Game/AI/AI/aiRemainsWaterChaseBulletRoot.h"

namespace uking::ai {

RemainsWaterChaseBulletRoot::RemainsWaterChaseBulletRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RemainsWaterChaseBulletRoot::~RemainsWaterChaseBulletRoot() {
    ;
}

bool RemainsWaterChaseBulletRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterChaseBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterChaseBulletRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterChaseBulletRoot::loadParams_() {
    getStaticParam(&mAtkMinDamage_s, "AtkMinDamage");
    getStaticParam(&mCheckPower_s, "CheckPower");
    getStaticParam(&mHighDamageAddSpd_s, "HighDamageAddSpd");
    getStaticParam(&mLowDamageAddSpd_s, "LowDamageAddSpd");
    getStaticParam(&mShootAddSpd_s, "ShootAddSpd");
    getStaticParam(&mResetASName_s, "ResetASName");
}

}  // namespace uking::ai
