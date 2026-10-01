#include "Game/AI/AI/aiViewWaitEndWhenAimed.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ViewWaitEndWhenAimed::ViewWaitEndWhenAimed(const InitArg& arg) : TimeredViewWait(arg) {}

ViewWaitEndWhenAimed::~ViewWaitEndWhenAimed() = default;

bool ViewWaitEndWhenAimed::init_(sead::Heap* heap) {
    if (!TimeredViewWait::init_(heap))
        return false;

    if (!mBoneName_s.isEmpty() && mActor->getModel())
        _a0.search(mActor->getModel(), mBoneName_s);
    else
        _a0.getKey().reset();
    return true;
}

void ViewWaitEndWhenAimed::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredViewWait::enter_(params);
}

void ViewWaitEndWhenAimed::leave_() {
    TimeredViewWait::leave_();
}

void ViewWaitEndWhenAimed::loadParams_() {
    TimeredViewWait::loadParams_();
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mAimedAngle_s, "AimedAngle");
    getStaticParam(&mBowRange_s, "BowRange");
    getStaticParam(&mBoneName_s, "BoneName");
}

}  // namespace uking::ai
