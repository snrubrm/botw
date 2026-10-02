#include "Game/AI/Action/actionBackFlip.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

BackFlip::BackFlip(const InitArg& arg) : RotateTurnToTarget(arg) {}

BackFlip::~BackFlip() = default;

bool BackFlip::init_(sead::Heap* heap) {
    return RotateTurnToTarget::init_(heap);
}

void BackFlip::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
}

void BackFlip::leave_() {
    RotateTurnToTarget::leave_();
    auto* actor = mActor;
    sub_7100738AA8(actor, 0.0f);
    sub_7100738428(actor, 0.1f);
}

void BackFlip::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mNearGrHeight_s, "NearGrHeight");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void BackFlip::calc_() {
    RotateTurnToTarget::calc_();
}

}  // namespace uking::action
