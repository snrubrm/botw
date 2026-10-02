#include "Game/AI/AI/aiTurnPreAction.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TurnPreAction::TurnPreAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TurnPreAction::~TurnPreAction() = default;

void TurnPreAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710072DDB8(*mTargetPos_d, mActor->getMtx(), *mTurnStartAngle_s)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("行動", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("ターン", &pack);
    }
}

void TurnPreAction::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("ターン")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("行動", &pack);
        return;
    }

    child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("行動")) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    } else {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

void TurnPreAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TurnPreAction::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
