#include "Game/AI/AI/aiFreezeInWaterSelect.h"

namespace uking::ai {

FreezeInWaterSelect::FreezeInWaterSelect(const InitArg& arg) : InWaterSelect(arg) {}

FreezeInWaterSelect::~FreezeInWaterSelect() = default;

void FreezeInWaterSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    InWaterSelect::enter_(params);
    *mIsKeepFreeze_a = false;
}

void FreezeInWaterSelect::leave_() {
    InWaterSelect::leave_();
    *mIsKeepFreeze_a = false;
}

void FreezeInWaterSelect::loadParams_() {
    InWaterSelect::loadParams_();
    getStaticParam(&mIceBreakTime_s, "IceBreakTime");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
}

bool FreezeInWaterSelect::isFinished() const {
    if (getCurrentChild()->isFinished())
        return true;
    return isCurrentChild("凍結解除") && ActionBase::isFinished();
}

}  // namespace uking::ai
