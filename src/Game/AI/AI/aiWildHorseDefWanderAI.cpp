#include "Game/AI/AI/aiWildHorseDefWanderAI.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

WildHorseDefWanderAI::WildHorseDefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WildHorseDefWanderAI::~WildHorseDefWanderAI() = default;

bool WildHorseDefWanderAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WildHorseDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 min = *mMinWaitTime_s;
    const f32 max = *mMaxWaitTime_s;
    _50 = sead::GlobalRandom::instance()->getF32Range(min, max);
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
