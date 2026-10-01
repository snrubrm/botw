#include "Game/AI/AI/aiEnemyChaseTargetAndAction.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyChaseTargetAndAction::EnemyChaseTargetAndAction(const InitArg& arg)
    : UnarmedEnemySearch(arg) {}

EnemyChaseTargetAndAction::~EnemyChaseTargetAndAction() = default;

void EnemyChaseTargetAndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

bool EnemyChaseTargetAndAction::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyChaseTargetAndAction::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
}

void EnemyChaseTargetAndAction::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mLostSpeed_s, "LostSpeed");
    getStaticParam(&mLostAng_s, "LostAng");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
