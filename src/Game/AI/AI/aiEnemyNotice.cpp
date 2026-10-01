#include "Game/AI/AI/aiEnemyNotice.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyNotice::EnemyNotice(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNotice::leave_() {
    sub_71005DB3EC(mActor);
}

void EnemyNotice::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
}

bool EnemyNotice::isFinished() const {
    return isCurrentChild("追跡") && getCurrentChild()->isFinished();
}

bool EnemyNotice::isFailed() const {
    return isCurrentChild("追跡") && getCurrentChild()->isFailed();
}

}  // namespace uking::ai
