#include "Game/AI/Action/actionPullOut.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

// NON_MATCHING: the original zeroes the params before the vtable store
PullOut::PullOut(const InitArg& arg) : ActionWithAS(arg) {}

PullOut::~PullOut() = default;

bool PullOut::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PullOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS("PullOut", false, 0, 0, -1.0f);
}

void PullOut::leave_() {
    sub_7100223B90();
    ActionWithAS::leave_();
}

void PullOut::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mAnimGrabPos_s, "AnimGrabPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void PullOut::calc_() {
    ActionWithAS::calc_();
    if (!sub_71005D83E8(mActor, 0))
        sub_7100223964();
    if (sub_71005DD780(mActor, 0x45, nullptr, 0, 0)) {
        _40._18.sub_710070E3D8(mActor);
        _40.sub_710070DCC0(mTargetActor_d, true);
    }
}

}  // namespace uking::action
