#include "Game/AI/Action/actionEnvSeEmitPointInsectPlayAction.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiXlinkHandle.h"

namespace uking::action {

EnvSeEmitPointInsectPlayAction::EnvSeEmitPointInsectPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

// TODO: the original fades the xlink2 handle (inline Handle code lib/xlink2 lacks) before deleting it
EnvSeEmitPointInsectPlayAction::~EnvSeEmitPointInsectPlayAction() = default;

bool EnvSeEmitPointInsectPlayAction::init_(sead::Heap* heap) {
    _28 = new (heap) xlink2::HandleSLink;
    return true;
}

void EnvSeEmitPointInsectPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnvSeEmitPointInsectPlayAction::leave_() {
    if (_28)
        xlink::fade(*_28, -1);
}

void EnvSeEmitPointInsectPlayAction::loadParams_() {}

void EnvSeEmitPointInsectPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
