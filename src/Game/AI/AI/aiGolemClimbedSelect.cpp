#include "Game/AI/AI/aiGolemClimbedSelect.h"

namespace uking::ai {

GolemClimbedSelect::GolemClimbedSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemClimbedSelect::~GolemClimbedSelect() = default;

bool GolemClimbedSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemClimbedSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mGolemClimbedTime_a > *mClimbTime_s)
        changeChild("対象よじ登り中", params);
    else
        changeChild("対象通常", params);
}

void GolemClimbedSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    if (isCurrentChild("対象通常")) {
        if (*mGolemClimbedTime_a > *mClimbTime_s)
            changeChild("対象よじ登り中");
    } else if (isCurrentChild("対象よじ登り中")) {
        if (*mGolemClimbedTime_a <= 0.0f)
            changeChild("対象通常");
    }
}

bool GolemClimbedSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool GolemClimbedSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void GolemClimbedSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemClimbedSelect::loadParams_() {
    getStaticParam(&mClimbTime_s, "ClimbTime");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai
