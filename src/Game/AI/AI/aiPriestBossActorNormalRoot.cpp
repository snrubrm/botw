#include "Game/AI/AI/aiPriestBossActorNormalRoot.h"

namespace uking::ai {

PriestBossActorNormalRoot::PriestBossActorNormalRoot(const InitArg& arg)
    : PriestBossActorRoot(arg) {}

PriestBossActorNormalRoot::~PriestBossActorNormalRoot() = default;

bool PriestBossActorNormalRoot::init_(sead::Heap* heap) {
    if (!PriestBossActorRoot::init_(heap))
        return false;
    _80.makeAllZero();
    return true;
}

void PriestBossActorNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

void PriestBossActorNormalRoot::leave_() {
    PriestBossActorRoot::leave_();
}

void PriestBossActorNormalRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
}

}  // namespace uking::ai
