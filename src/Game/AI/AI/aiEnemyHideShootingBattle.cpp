#include "Game/AI/AI/aiEnemyHideShootingBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyHideShootingBattle::EnemyHideShootingBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHideShootingBattle::~EnemyHideShootingBattle() = default;

void EnemyHideShootingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("隠れる", &pack);
}

bool EnemyHideShootingBattle::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyHideShootingBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyHideShootingBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHideShootingBattle::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
