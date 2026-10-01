#include "Game/AI/AI/aiRangeHeightSelectTwoAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RangeHeightSelectTwoAction::RangeHeightSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

RangeHeightSelectTwoAction::~RangeHeightSelectTwoAction() = default;

bool RangeHeightSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void RangeHeightSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void RangeHeightSelectTwoAction::calc_() {
    RangeSelectAction::calc_();
}

void RangeHeightSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void RangeHeightSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
    getStaticParam(&mMaxY_s, "MaxY");
    getStaticParam(&mMinY_s, "MinY");
}

bool RangeHeightSelectTwoAction::m36() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 diff_y = mTargetPos_d->y - pos.y;
    if (*mMinY_s > diff_y || diff_y > *mMaxY_s)
        return true;
    return RangeSelectTwoAction::m36();
}

}  // namespace uking::ai
