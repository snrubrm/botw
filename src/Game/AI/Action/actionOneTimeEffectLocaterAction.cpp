#include "Game/AI/Action/actionOneTimeEffectLocaterAction.h"

namespace uking::action {

OneTimeEffectLocaterAction::OneTimeEffectLocaterAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OneTimeEffectLocaterAction::~OneTimeEffectLocaterAction() = default;

bool OneTimeEffectLocaterAction::init_(sead::Heap* heap) {
    _1c = false;
    return true;
}

void OneTimeEffectLocaterAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OneTimeEffectLocaterAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void OneTimeEffectLocaterAction::loadParams_() {}

void OneTimeEffectLocaterAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
