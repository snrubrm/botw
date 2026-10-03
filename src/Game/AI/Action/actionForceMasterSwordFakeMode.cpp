#include "Game/AI/Action/actionForceMasterSwordFakeMode.h"
#include "Game/Damage/dmgInfoManager.h"

namespace uking::action {

ForceMasterSwordFakeMode::ForceMasterSwordFakeMode(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceMasterSwordFakeMode::~ForceMasterSwordFakeMode() = default;

bool ForceMasterSwordFakeMode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ForceMasterSwordFakeMode::oneShot_() {
    if (auto* mgr = dmg::DamageInfoMgr::instance())
        mgr->setMasterSwordDisableTrueForm(true);
    return ksys::act::ai::Action::oneShot_();
}

void ForceMasterSwordFakeMode::loadParams_() {}

}  // namespace uking::action
