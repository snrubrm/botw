#include "Game/AI/AI/aiWizzrobeCombatMove.h"

namespace uking::ai {

WizzrobeCombatMove::WizzrobeCombatMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
WizzrobeCombatMove::~WizzrobeCombatMove() {
    ;
}

bool WizzrobeCombatMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeCombatMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeCombatMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeCombatMove::loadParams_() {
    getStaticParam(&mMoveCountMin_s, "MoveCountMin");
    getStaticParam(&mMoveCountMax_s, "MoveCountMax");
    getStaticParam(&mDistY_s, "DistY");
    getStaticParam(&mRetryLength_s, "RetryLength");
    getStaticParam(&mMaxDistXZ_s, "MaxDistXZ");
    getStaticParam(&mMinDistXZ_s, "MinDistXZ");
    getStaticParam(&mEscapeLength_s, "EscapeLength");
    getStaticParam(&mIgnoreHideActionASName_s, "IgnoreHideActionASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAttPos_d, "AttPos");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

bool WizzrobeCombatMove::isFinished() const {
    if (isCurrentChild("現れる") && getCurrentChild()->isFinished())
        return true;
    return ksys::act::ai::Ai::isFinished();
}

}  // namespace uking::ai
