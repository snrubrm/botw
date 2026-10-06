#include "Game/AI/Action/actionDemoVoiceTrigger.h"
#include <aal/aalArbiter.h>
#include <aal/aalSystemAccessor.h>

namespace uking::action {

DemoVoiceTrigger::DemoVoiceTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVoiceTrigger::~DemoVoiceTrigger() = default;

bool DemoVoiceTrigger::init_(sead::Heap* heap) {
    mEmitter = aal::SystemAccessor::getArbiter()->allocEmitter(heap, "demoVoiceTrigger");
    _50 = false;
    return true;
}

void DemoVoiceTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoVoiceTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoVoiceTrigger::loadParams_() {
    getDynamicParam(&mIsHideCaption_d, "IsHideCaption");
    getDynamicParam(&mLabel_d, "Label");
    getDynamicParam(&mActorInstance_d, "ActorInstance");
}

void DemoVoiceTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
