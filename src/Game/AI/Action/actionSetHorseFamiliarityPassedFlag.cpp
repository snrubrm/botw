#include "Game/AI/Action/actionSetHorseFamiliarityPassedFlag.h"
#include "Game/gameHorseMgr.h"

namespace uking::action {

SetHorseFamiliarityPassedFlag::SetHorseFamiliarityPassedFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetHorseFamiliarityPassedFlag::~SetHorseFamiliarityPassedFlag() = default;

bool SetHorseFamiliarityPassedFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetHorseFamiliarityPassedFlag::loadParams_() {}

bool SetHorseFamiliarityPassedFlag::oneShot_() {
    if (auto* horse_mgr = HorseMgr::instance())
        return horse_mgr->sub_7100E87710();
    return false;
}

}  // namespace uking::action
