#include "Game/AI/Behavior/behaviorForceDispLifeGage.h"

namespace uking::behavior {

ForceDispLifeGage::ForceDispLifeGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceDispLifeGage::~ForceDispLifeGage() = default;

bool ForceDispLifeGage::m6(sead::Heap* heap) {
    return true;
}

void ForceDispLifeGage::loadParams() {
    getStaticParam(&mIsOnlyPlayer_s, "IsOnlyPlayer");
}

}  // namespace uking::behavior
