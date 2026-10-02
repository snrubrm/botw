#include "Game/AI/Behavior/behaviorBeastGanonBgmCtrl.h"

namespace uking::behavior {

BeastGanonBgmCtrl::BeastGanonBgmCtrl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BeastGanonBgmCtrl::~BeastGanonBgmCtrl() = default;

bool BeastGanonBgmCtrl::hasUpdateForPreDeleteCb() {
    return true;
}

void BeastGanonBgmCtrl::m9() {}

void BeastGanonBgmCtrl::loadParams() {
    getStaticParam(&mLevel_s, "Level");
}

bool BeastGanonBgmCtrl::m6(sead::Heap* heap) {
    _30 = false;
    return true;
}

}  // namespace uking::behavior
