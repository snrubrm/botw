#include "Game/AI/AI/aiPriestBossActorRoot.h"

namespace uking::ai {

PriestBossActorRoot::PriestBossActorRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossActorRoot::~PriestBossActorRoot() = default;

bool PriestBossActorRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossActorRoot::calc_() {
    PriestBossMode::calc_();
}

void PriestBossActorRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossActorRoot::loadParams_() {
    PriestBossMode::loadParams_();
}

bool PriestBossActorRoot::handleMessage_(const ksys::Message* message) {
    return false;
}

}  // namespace uking::ai
