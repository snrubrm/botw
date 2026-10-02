#include "Game/AI/Behavior/behaviorPriestBossUrbosasFuryEShock.h"

namespace uking::behavior {

PriestBossUrbosasFuryEShock::PriestBossUrbosasFuryEShock(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

PriestBossUrbosasFuryEShock::~PriestBossUrbosasFuryEShock() = default;

bool PriestBossUrbosasFuryEShock::m6(sead::Heap* heap) {
    return true;
}

void PriestBossUrbosasFuryEShock::m7() {}

void PriestBossUrbosasFuryEShock::m9() {}

void PriestBossUrbosasFuryEShock::loadParams() {
    getStaticParam(&mElectricShock_s, "ElectricShock");
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
}

void PriestBossUrbosasFuryEShock::m8() {
    *mPriestBossUrbosasFuryEShock_a = *mElectricShock_s;
}

}  // namespace uking::behavior
