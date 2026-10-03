#include "Game/AI/AI/aiNPCReaction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

NPCReaction::NPCReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCReaction::~NPCReaction() {
    ;
}

void NPCReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mReactionId_d) {
    case 0: {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mStaggerDir_d, "MoveDir", -1);
        changeChild("よろける", &pack);
        break;
    }
    case 1: {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mGazeASName_d, "DynASName", -1);
        changeChild("注視する", &pack);
        break;
    }
    case 2: {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mMessageId_d, "MessageId", -1);
        pack.addVec3(getPlayerPosition(), "TargetPos", -1);
        changeChild("吹き出し", &pack);
        break;
    }
    }
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
