#include "Game/AI/Behavior/behaviorLookAtOwnedHorse.h"

namespace uking::behavior {

LookAtOwnedHorse::LookAtOwnedHorse(const InitArg& arg) : InterestNeckControl(arg) {}

LookAtOwnedHorse::~LookAtOwnedHorse() = default;

void LookAtOwnedHorse::m8() {
    InterestNeckControl::m8();
}

void LookAtOwnedHorse::m9() {
    InterestNeckControl::m9();
}

void LookAtOwnedHorse::loadParams() {
    InterestNeckControl::loadParams();
    getStaticParam(&mDistance_s, "Distance");
}

}  // namespace uking::behavior
