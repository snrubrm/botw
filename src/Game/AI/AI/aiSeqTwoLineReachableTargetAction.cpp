#include "Game/AI/AI/aiSeqTwoLineReachableTargetAction.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

SeqTwoLineReachableTargetAction::SeqTwoLineReachableTargetAction(const InitArg& arg)
    : SeqTwoLineReachableTargetActionBase(arg) {}

SeqTwoLineReachableTargetAction::~SeqTwoLineReachableTargetAction() = default;

bool SeqTwoLineReachableTargetAction::init_(sead::Heap* heap) {
    return SeqTwoLineReachableTargetActionBase::init_(heap);
}

void SeqTwoLineReachableTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoLineReachableTargetActionBase::enter_(params);
}

void SeqTwoLineReachableTargetAction::calc_() {
    SeqTwoLineReachableTargetActionBase::calc_();
}

void SeqTwoLineReachableTargetAction::leave_() {
    SeqTwoLineReachableTargetActionBase::leave_();
}

void SeqTwoLineReachableTargetAction::loadParams_() {
    SeqTwoLineReachableTargetActionBase::loadParams_();
}

const sead::Vector3f* SeqTwoLineReachableTargetAction::m36() {
    return &sub_71005D9330(mActor);
}

}  // namespace uking::ai
