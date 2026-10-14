#include "Game/Actor/AI/aiSeqTwoLineReachableTargetAction.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

SeqTwoLineReachableTargetAction::SeqTwoLineReachableTargetAction(const InitArg& arg)
    : SeqTwoLineReachableTarget(arg) {}

SeqTwoLineReachableTargetAction::~SeqTwoLineReachableTargetAction() = default;

bool SeqTwoLineReachableTargetAction::init_(sead::Heap* heap) {
    return SeqTwoLineReachableTarget::init_(heap);
}

void SeqTwoLineReachableTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoLineReachableTarget::enter_(params);
}

void SeqTwoLineReachableTargetAction::calc_() {
    SeqTwoLineReachableTarget::calc_();
}

void SeqTwoLineReachableTargetAction::leave_() {
    SeqTwoLineReachableTarget::leave_();
}

void SeqTwoLineReachableTargetAction::loadParams_() {
    SeqTwoLineReachableTarget::loadParams_();
}

const sead::Vector3f* SeqTwoLineReachableTargetAction::m36() {
    return &sub_71005D9330(mActor);
}

}  // namespace uking::ai
