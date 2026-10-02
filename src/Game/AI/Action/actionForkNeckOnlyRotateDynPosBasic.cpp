#include "Game/AI/Action/actionForkNeckOnlyRotateDynPosBasic.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkNeckOnlyRotateDynPosBasic::ForkNeckOnlyRotateDynPosBasic(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNeckOnlyRotateDynPosBasic::~ForkNeckOnlyRotateDynPosBasic() = default;

bool ForkNeckOnlyRotateDynPosBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNeckOnlyRotateDynPosBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkNeckOnlyRotateDynPosBasic::leave_() {
    sub_71005DB3B8(mActor);
}

void ForkNeckOnlyRotateDynPosBasic::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkNeckOnlyRotateDynPosBasic::calc_() {
    sub_71005DB110(mActor, *mTargetPos_d);
}

}  // namespace uking::action
