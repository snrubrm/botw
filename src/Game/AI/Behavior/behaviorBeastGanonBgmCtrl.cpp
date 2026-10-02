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

}  // namespace uking::behavior
