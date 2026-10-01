#include "Game/AI/AI/aiJumpAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

JumpAttack::JumpAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void JumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("攻撃準備", &pack);
}

void JumpAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void JumpAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool JumpAttack::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("攻撃") && getCurrentChild()->isFinished());
}

void JumpAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃")) {
            setFinished();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("攻撃", &pack);
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
