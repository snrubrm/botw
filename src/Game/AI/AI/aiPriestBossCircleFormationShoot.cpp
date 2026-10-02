#include "Game/AI/AI/aiPriestBossCircleFormationShoot.h"

namespace uking::ai {

PriestBossCircleFormationShoot::PriestBossCircleFormationShoot(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationShoot::~PriestBossCircleFormationShoot() = default;

bool PriestBossCircleFormationShoot::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
}

void PriestBossCircleFormationShoot::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossCircleFormationShoot::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

bool PriestBossCircleFormationShoot::m36() {
    if (isCurrentChild("陣形作成後待機"))
        return false;
    return PriestBossFormation::m36();
}

}  // namespace uking::ai
