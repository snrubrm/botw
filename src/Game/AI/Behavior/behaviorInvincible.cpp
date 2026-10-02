#include "Game/AI/Behavior/behaviorInvincible.h"

namespace uking::behavior {

Invincible::Invincible(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

Invincible::~Invincible() = default;

bool Invincible::m6(sead::Heap* heap) {
    return true;
}

void Invincible::m7() {}

void Invincible::loadParams() {

}

}  // namespace uking::behavior
