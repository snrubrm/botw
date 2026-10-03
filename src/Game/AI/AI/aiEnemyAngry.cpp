#include "Game/AI/AI/aiEnemyAngry.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyAngry::EnemyAngry(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710072DDB8(*mTargetPos_d, mActor->getMtx(), *mTurnAng_s)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("怒り", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("回転", &pack);
    }
}

void EnemyAngry::loadParams_() {
    getStaticParam(&mTurnAng_s, "TurnAng");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyAngry::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("怒り")) {
            setFinished();
        } else if (isCurrentChild("回転")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("怒り", &pack);
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
