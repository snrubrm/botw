#include "Game/AI/AI/aiLeadToTarget.h"

namespace uking::ai {

LeadToTarget::LeadToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeadToTarget::~LeadToTarget() = default;

bool LeadToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeadToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _94 = false;
    _78 = 0;
    _7c = 0;
    sub_710047FE18();
}

void LeadToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeadToTarget::loadParams_() {
    if (getStaticParam(&mSuccessRadius_s, "SuccessRadius"))
        _84 = *mSuccessRadius_s * *mSuccessRadius_s;
    if (getStaticParam(&mWaitDistance_s, "WaitDistance"))
        _88 = *mWaitDistance_s * *mWaitDistance_s;
    if (getStaticParam(&mResumeLeadDistance_s, "ResumeLeadDistance"))
        _8c = *mResumeLeadDistance_s * *mResumeLeadDistance_s;
    if (getStaticParam(&mOkPathFailRange_s, "OkPathFailRange"))
        _90 = *mOkPathFailRange_s * *mOkPathFailRange_s;
    getStaticParam(&mDontWaitIfLeaderIsAhead_s, "DontWaitIfLeaderIsAhead");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
    getStaticParam(&mWaitFramesAfterArrive_s, "WaitFramesAfterArrive");
}

}  // namespace uking::ai
