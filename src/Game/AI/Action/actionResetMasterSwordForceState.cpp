#include "Game/AI/Action/actionResetMasterSwordForceState.h"
#include "Game/Damage/dmgInfoManager.h"

namespace uking::action {

ResetMasterSwordForceState::ResetMasterSwordForceState(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetMasterSwordForceState::~ResetMasterSwordForceState() = default;

bool ResetMasterSwordForceState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ResetMasterSwordForceState::oneShot_() {
    if (auto* mgr = dmg::DamageInfoMgr::instance())
        mgr->setMasterSwordDisableTrueForm(false);
    return ksys::act::ai::Action::oneShot_();
}

void ResetMasterSwordForceState::loadParams_() {}

}  // namespace uking::action
