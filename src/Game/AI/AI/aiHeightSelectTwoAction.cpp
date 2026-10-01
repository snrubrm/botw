#include "Game/AI/AI/aiHeightSelectTwoAction.h"

namespace uking::ai {

HeightSelectTwoAction::HeightSelectTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HeightSelectTwoAction::~HeightSelectTwoAction() = default;

void HeightSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool HeightSelectTwoAction::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool HeightSelectTwoAction::isFinished() const {
    return getCurrentChild()->isFinished();
}

void HeightSelectTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HeightSelectTwoAction::loadParams_() {
    getStaticParam(&mSelectCheckInterval_s, "SelectCheckInterval");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
