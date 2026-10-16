#include "Game/Actor/Behavior/behaviorPriestBossUrbosasFuryEShock.h"

namespace uking::behavior {

PriestBossUrbosasFuryEShock::PriestBossUrbosasFuryEShock(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

PriestBossUrbosasFuryEShock::~PriestBossUrbosasFuryEShock() = default;

bool PriestBossUrbosasFuryEShock::init_(sead::Heap* heap) {
    return true;
}

void PriestBossUrbosasFuryEShock::calc() {}

void PriestBossUrbosasFuryEShock::leave() {}

void PriestBossUrbosasFuryEShock::loadParams() {
    getStaticParam(&mElectricShock_s, "ElectricShock");
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
}

void PriestBossUrbosasFuryEShock::enter() {
    *mPriestBossUrbosasFuryEShock_a = *mElectricShock_s;
}

}  // namespace uking::behavior
