#include "Game/AI/AI/aiEnemyAngry.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyAngry::EnemyAngry(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
