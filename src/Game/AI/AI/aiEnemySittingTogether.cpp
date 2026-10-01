#include "Game/AI/AI/aiEnemySittingTogether.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemySittingTogether::EnemySittingTogether(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemySittingTogether::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemySittingTogether::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (sead::GlobalRandom::instance()->getU32(100) < 50)
        changeChild("座る", &pack);
    else
        changeChild("騒ぐ", &pack);
}

void EnemySittingTogether::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySittingTogether::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mIsNextActionReserved_a, "IsNextActionReserved");
}

void EnemySittingTogether::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        if (!*mIsNextActionReserved_a && isCurrentChild("座る"))
            changeChild("騒ぐ", &pack);
        else
            changeChild("座る", &pack);
    } else {
        child->isChangeable();
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
