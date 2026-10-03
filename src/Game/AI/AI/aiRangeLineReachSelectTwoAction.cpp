#include "Game/AI/AI/aiRangeLineReachSelectTwoAction.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RangeLineReachSelectTwoAction::RangeLineReachSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

RangeLineReachSelectTwoAction::~RangeLineReachSelectTwoAction() = default;

bool RangeLineReachSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void RangeLineReachSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void RangeLineReachSelectTwoAction::calc_() {
    RangeSelectTwoAction::calc_();
}

void RangeLineReachSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void RangeLineReachSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
}

bool RangeLineReachSelectTwoAction::m36() {
    if (RangeSelectTwoAction::m36())
        return true;
    auto* actor = mActor;
    sead::Vector3f from;
    actor->getMtx().getTranslation(from);
    return !sub_710072F854(actor, from, *mTargetPos_d, nullptr, sub_7100539F84(), -1);
}

}  // namespace uking::ai
