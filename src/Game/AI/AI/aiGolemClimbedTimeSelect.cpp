#include "Game/AI/AI/aiGolemClimbedTimeSelect.h"

namespace uking::ai {

GolemClimbedTimeSelect::GolemClimbedTimeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemClimbedTimeSelect::~GolemClimbedTimeSelect() = default;

bool GolemClimbedTimeSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool GolemClimbedTimeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GolemClimbedTimeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemClimbedTimeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mGolemClimbedTime_a > *mLimitTime_s)
        changeChild("時間超過", params);
    else
        changeChild("時間内", params);
}

void GolemClimbedTimeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    if (isCurrentChild("時間内") && *mGolemClimbedTime_a > *mLimitTime_s)
        changeChild("時間超過");
}

void GolemClimbedTimeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemClimbedTimeSelect::loadParams_() {
    getStaticParam(&mLimitTime_s, "LimitTime");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai
