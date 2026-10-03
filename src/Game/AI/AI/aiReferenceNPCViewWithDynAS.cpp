#include "Game/AI/AI/aiReferenceNPCViewWithDynAS.h"

namespace uking::ai {

ReferenceNPCViewWithDynAS::ReferenceNPCViewWithDynAS(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReferenceNPCViewWithDynAS::~ReferenceNPCViewWithDynAS() = default;

bool ReferenceNPCViewWithDynAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReferenceNPCViewWithDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReferenceNPCViewWithDynAS::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original computes the later params' `this + off` addresses before the first call
// and keeps them in callee-saved registers (extra frame slot); same family as WeaponOnetimeUse
void ReferenceNPCViewWithDynAS::loadParams_() {
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
    getStaticParam(&mParams.mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mParams.mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
}

bool ReferenceNPCViewWithDynAS::isFinished() const {
    return isCurrentChild("待機") && getCurrentChild()->isFinished();
}

}  // namespace uking::ai
