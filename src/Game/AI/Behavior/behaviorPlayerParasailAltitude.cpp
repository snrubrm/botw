#include "Game/AI/Behavior/behaviorPlayerParasailAltitude.h"

namespace uking::behavior {

PlayerParasailAltitude::PlayerParasailAltitude(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

PlayerParasailAltitude::~PlayerParasailAltitude() = default;

bool PlayerParasailAltitude::m6(sead::Heap* heap) {
    return true;
}

void PlayerParasailAltitude::loadParams() {

}

}  // namespace uking::behavior
