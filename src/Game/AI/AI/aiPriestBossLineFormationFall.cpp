#include "Game/AI/AI/aiPriestBossLineFormationFall.h"

namespace uking::ai {

PriestBossLineFormationFall::PriestBossLineFormationFall(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationFall::~PriestBossLineFormationFall() = default;

bool PriestBossLineFormationFall::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    m43();
    _94 = false;
}

void PriestBossLineFormationFall::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationFall::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mWarpHightOffset_s, "WarpHightOffset");
}

}  // namespace uking::ai
