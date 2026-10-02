#include "Game/AI/Behavior/behaviorNeckParamChange.h"

namespace uking::behavior {

NeckParamChange::NeckParamChange(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckParamChange::~NeckParamChange() = default;

bool NeckParamChange::m6(sead::Heap* heap) {
    return true;
}

void NeckParamChange::loadParams() {
    getStaticParam(&mULimit_s, "ULimit");
    getStaticParam(&mDLimit_s, "DLimit");
    getStaticParam(&mLLimit_s, "LLimit");
    getStaticParam(&mRLimit_s, "RLimit");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRetRotRatio_s, "RetRotRatio");
    getStaticParam(&mMinRotate_s, "MinRotate");
    getStaticParam(&mMaxRotate_s, "MaxRotate");
    getStaticParam(&mOffsetLR_s, "OffsetLR");
    getStaticParam(&mOffsetUD_s, "OffsetUD");
}

}  // namespace uking::behavior
