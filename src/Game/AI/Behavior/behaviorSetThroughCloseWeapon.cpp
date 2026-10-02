#include "Game/AI/Behavior/behaviorSetThroughCloseWeapon.h"

namespace uking::behavior {

// NON_MATCHING: the object at 0x28 is not declared yet (placeholder bytes)
SetThroughCloseWeapon::SetThroughCloseWeapon(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetThroughCloseWeapon::~SetThroughCloseWeapon() = default;

bool SetThroughCloseWeapon::m6(sead::Heap* heap) {
    return true;
}

void SetThroughCloseWeapon::m7() {}

void SetThroughCloseWeapon::loadParams() {

}

}  // namespace uking::behavior
