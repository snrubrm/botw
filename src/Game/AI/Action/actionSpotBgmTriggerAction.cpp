#include "Game/AI/Action/actionSpotBgmTriggerAction.h"

namespace uking::action {

SpotBgmTriggerAction::SpotBgmTriggerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SpotBgmTriggerAction::~SpotBgmTriggerAction() {
    if (_48) {
        _48->_8.sub_710101D9A4();
        delete _48;
        _48 = nullptr;
    }
}

bool SpotBgmTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_48) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBBE4(_48);
    }
}

void SpotBgmTriggerAction::leave_() {
    if (_48) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBCA0(_48);
    }
}

void SpotBgmTriggerAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

void SpotBgmTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
