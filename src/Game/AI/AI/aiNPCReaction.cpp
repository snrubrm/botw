#include "Game/AI/AI/aiNPCReaction.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

NPCReaction::NPCReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCReaction::~NPCReaction() {
    ;
}

void NPCReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReaction::calc_() {
    if (isCurrentChild("よろける")) {
        if (getCurrentChild()->isFinished())
            setFinished();
    } else if (isCurrentChild("注視する")) {
        if (!*mIsReceiveInterest2_d)
            setFinished();
    } else if (isCurrentChild("吹き出し")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
        getCurrentChild()->setDynamicParam(getPlayerPosition(), "TargetPos");
    }
}

void NPCReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReaction::loadParams_() {
    getDynamicParam(&mReactionId_d, "ReactionId");
    getDynamicParam(&mIsReceiveInterest2_d, "IsReceiveInterest2");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mGazeASName_d, "GazeASName");
    getDynamicParam(&mStaggerDir_d, "StaggerDir");
}

}  // namespace uking::ai
