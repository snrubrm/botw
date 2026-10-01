#include "Game/AI/AI/aiSeqTargetTwoAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SeqTargetTwoAction::SeqTargetTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void SeqTargetTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack params_;
    params_.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("先行動", &params_);
}

void SeqTargetTwoAction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed() && *mIsFinishedByFailAction_s) {
            setFailed();
            return;
        }
        if (!isCurrentChild("先行動")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
            return;
        }
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("後行動", &params);
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void SeqTargetTwoAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
