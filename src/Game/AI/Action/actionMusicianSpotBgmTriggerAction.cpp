#include "Game/AI/Action/actionMusicianSpotBgmTriggerAction.h"

namespace uking::action {

MusicianSpotBgmTriggerAction::MusicianSpotBgmTriggerAction(const InitArg& arg)
    : SpotBgmTriggerAction(arg) {}

MusicianSpotBgmTriggerAction::~MusicianSpotBgmTriggerAction() = default;

bool MusicianSpotBgmTriggerAction::init_(sead::Heap* heap) {
    return SpotBgmTriggerAction::init_(heap);
}

void MusicianSpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SpotBgmTriggerAction::enter_(params);
    if (_48)
        _48->_368 |= 0x400;
}

void MusicianSpotBgmTriggerAction::leave_() {
    SpotBgmTriggerAction::leave_();
}

void MusicianSpotBgmTriggerAction::loadParams_() {
    SpotBgmTriggerAction::loadParams_();
}

void MusicianSpotBgmTriggerAction::calc_() {
    SpotBgmTriggerAction::calc_();
}

}  // namespace uking::action
