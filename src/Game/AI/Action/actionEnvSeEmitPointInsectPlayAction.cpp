#include "Game/AI/Action/actionEnvSeEmitPointInsectPlayAction.h"
#include <xlink2/xlink2Handle.h>

namespace uking::action {

EnvSeEmitPointInsectPlayAction::EnvSeEmitPointInsectPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

// TODO: the original fades the xlink2 handle (inline Handle code lib/xlink2 lacks) before deleting it
EnvSeEmitPointInsectPlayAction::~EnvSeEmitPointInsectPlayAction() = default;

bool EnvSeEmitPointInsectPlayAction::init_(sead::Heap* heap) {
    _28 = new (heap) xlink2::Handle;
    return true;
}

void EnvSeEmitPointInsectPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnvSeEmitPointInsectPlayAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSeEmitPointInsectPlayAction::loadParams_() {}

void EnvSeEmitPointInsectPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
