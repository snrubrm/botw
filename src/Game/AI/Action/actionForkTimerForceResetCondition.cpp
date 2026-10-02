#include "Game/AI/Action/actionForkTimerForceResetCondition.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::action {

ForkTimerForceResetCondition::ForkTimerForceResetCondition(const InitArg& arg) : ForkTimer(arg) {}

ForkTimerForceResetCondition::~ForkTimerForceResetCondition() = default;

bool ForkTimerForceResetCondition::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void ForkTimerForceResetCondition::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkTimerForceResetCondition::leave_() {
    ForkTimer::leave_();
}

void ForkTimerForceResetCondition::loadParams_() {
    ForkTimer::loadParams_();
    getStaticParam(&mResetCondition_s, "ResetCondition");
}

void ForkTimerForceResetCondition::calc_() {
    ForkTimer::calc_();
    if (_30 <= 0.0f) {
        if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
            if (*mResetCondition_s >= 0)
                actor->m149(*mResetCondition_s);
            else
                actor->m150();
        }
    }
}

}  // namespace uking::action
