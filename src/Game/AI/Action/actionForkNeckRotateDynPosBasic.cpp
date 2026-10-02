#include "Game/AI/Action/actionForkNeckRotateDynPosBasic.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkNeckRotateDynPosBasic::ForkNeckRotateDynPosBasic(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNeckRotateDynPosBasic::~ForkNeckRotateDynPosBasic() = default;

bool ForkNeckRotateDynPosBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNeckRotateDynPosBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkNeckRotateDynPosBasic::leave_() {
    sub_71005DB3EC(mActor);
}

void ForkNeckRotateDynPosBasic::loadParams_() {
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkNeckRotateDynPosBasic::calc_() {
    if (*mUseSimpleOffset_s)
        sub_71005DB1D8(mActor, *mTargetPos_d);
    else
        sub_71005DB068(mActor, *mTargetPos_d);
}

}  // namespace uking::action
