#include "Game/AI/AI/aiNPCWander.h"

namespace uking::ai {

NPCWander::NPCWander(const InitArg& arg) : NPCTravelBase(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCWander::~NPCWander() {
    ;
}

bool NPCWander::init_(sead::Heap* heap) {
    return NPCTravelBase::init_(heap);
}

void NPCWander::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTravelBase::enter_(params);
}

void NPCWander::leave_() {
    NPCTravelBase::leave_();
}

void NPCWander::loadParams_() {
    NPCTravelBase::loadParams_();
    getStaticParam(&mRainWaitTime_s, "RainWaitTime");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mRailUpdateDistRate_s, "RailUpdateDistRate");
    getStaticParam(&mRainDestination_s, "RainDestination");
    getStaticParam(&mNormalASKeyName_s, "NormalASKeyName");
    getStaticParam(&mRainASKeyName_s, "RainASKeyName");
    getStaticParam(&mRailUniqueName_s, "RailUniqueName");
    getDynamicParam(&mIsPathRest_d, "IsPathRest");
}

}  // namespace uking::ai
