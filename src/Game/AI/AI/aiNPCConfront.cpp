#include "Game/AI/AI/aiNPCConfront.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

NPCConfront::NPCConfront(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCConfront::~NPCConfront() = default;

bool NPCConfront::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCConfront::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCConfront::leave_() {
    sub_71005D7518(mActor, true);
}

void NPCConfront::loadParams_() {
    getStaticParam(&mCounterGuardCount_s, "CounterGuardCount");
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mCounterRate_s, "CounterRate");
    getStaticParam(&mDirectTurnAngle_s, "DirectTurnAngle");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
