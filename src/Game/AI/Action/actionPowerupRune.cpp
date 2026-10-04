#include "Game/AI/Action/actionPowerupRune.h"

// Declaration only: existing CSV name at 0x7100ede640; source namespace is unknown.
void powerupRuneStuff(bool enabled);

namespace uking::action {

PowerupRune::PowerupRune(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PowerupRune::~PowerupRune() = default;

bool PowerupRune::oneShot_() {
    if (*mRuneType_d == 2)
        powerupRuneStuff(true);
    return true;
}

bool PowerupRune::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PowerupRune::loadParams_() {
    getDynamicParam(&mRuneType_d, "RuneType");
}

}  // namespace uking::action
