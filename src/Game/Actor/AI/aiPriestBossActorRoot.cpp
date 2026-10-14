#include "Game/Actor/AI/aiPriestBossActorRoot.h"

namespace uking::ai {

PriestBossActorRoot::PriestBossActorRoot(const InitArg& arg) : PriestBoss(arg) {}

PriestBossActorRoot::~PriestBossActorRoot() = default;

bool PriestBossActorRoot::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossActorRoot::calc_() {
    PriestBoss::calc_();
}

void PriestBossActorRoot::leave_() {
    PriestBoss::leave_();
}

void PriestBossActorRoot::loadParams_() {
    PriestBoss::loadParams_();
}

bool PriestBossActorRoot::handleMessage_(const ksys::Message* message) {
    return false;
}

}  // namespace uking::ai
