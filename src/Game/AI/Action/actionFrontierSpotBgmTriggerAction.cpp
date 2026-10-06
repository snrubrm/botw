#include "Game/AI/Action/actionFrontierSpotBgmTriggerAction.h"

namespace uking::action {

FrontierSpotBgmTriggerAction::FrontierSpotBgmTriggerAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

FrontierSpotBgmTriggerAction::~FrontierSpotBgmTriggerAction() {
    if (_60) {
        _60->_8.sub_710101D9A4();
        delete _60;
        _60 = nullptr;
    }
}

bool FrontierSpotBgmTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FrontierSpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_60) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBBE4(_60);
    }
}

void FrontierSpotBgmTriggerAction::leave_() {
    if (_60) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBCA0(_60);
    }
}

void FrontierSpotBgmTriggerAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
    getMapUnitParam(&mSpotBgmLifeScaleMargin_m, "SpotBgmLifeScaleMargin");
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
    getMapUnitParam(&mShape_m, "Shape");
}

void FrontierSpotBgmTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
