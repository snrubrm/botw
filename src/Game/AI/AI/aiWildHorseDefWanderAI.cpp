#include "Game/AI/AI/aiWildHorseDefWanderAI.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

WildHorseDefWanderAI::WildHorseDefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WildHorseDefWanderAI::~WildHorseDefWanderAI() = default;

bool WildHorseDefWanderAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads both params before the GlobalRandom instance
void WildHorseDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = sead::GlobalRandom::instance()->getF32Range(*mMinWaitTime_s, *mMaxWaitTime_s);
    _56 = 0;
    changeChild("待機");
}

void WildHorseDefWanderAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WildHorseDefWanderAI::loadParams_() {
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
}

}  // namespace uking::ai
