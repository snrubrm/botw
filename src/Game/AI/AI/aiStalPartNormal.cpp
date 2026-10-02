#include "Game/AI/AI/aiStalPartNormal.h"

namespace uking::ai {

// NON_MATCHING: the two param-zeroing stp stores are scheduled in the opposite order
StalPartNormal::StalPartNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartNormal::~StalPartNormal() = default;

bool StalPartNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartNormal::loadParams_() {
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mCatchArea_s, "CatchArea");
    getStaticParam(&mWaitTimer_s, "WaitTimer");
    getStaticParam(&mTgtOffset_s, "TgtOffset");
}

bool StalPartNormal::handleMessage_(const ksys::Message& message) {
    if (_e8 <= sead::Mathf::epsilon() && !_68._30 && !isCurrentChild("行動禁止") &&
        _68.m2(message)) {
        if (_58 == _68._38.mLink)
            _68.x();
        return true;
    }
    return false;
}

}  // namespace uking::ai
