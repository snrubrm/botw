#include "Game/AI/Action/actionStopAllDemoSoundAction.h"

namespace uking::action {

StopAllDemoSoundAction::StopAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopAllDemoSoundAction::~StopAllDemoSoundAction() = default;

bool StopAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopAllDemoSoundAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 1.0f;
}

void StopAllDemoSoundAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopAllDemoSoundAction::loadParams_() {}

void StopAllDemoSoundAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
