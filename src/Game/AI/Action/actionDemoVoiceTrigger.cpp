#include "Game/AI/Action/actionDemoVoiceTrigger.h"
#include <aal/aalArbiter.h>
#include <aal/aalSystemAccessor.h>
#include "Game/UI/uiUI.h"

namespace uking::action {

DemoVoiceTrigger::DemoVoiceTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVoiceTrigger::~DemoVoiceTrigger() {
    if (mEmitter) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            arbiter->freeEmitter(mEmitter);
            mEmitter = nullptr;
        }
    }
}

bool DemoVoiceTrigger::init_(sead::Heap* heap) {
    mEmitter = aal::SystemAccessor::getArbiter()->allocEmitter(heap, "demoVoiceTrigger");
    _50 = false;
    return true;
}

void DemoVoiceTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the stack temporaries for the dynamic-param fetches are laid out differently
    // (ours reuses slots; the original keeps an extra saved register and slot), and our call to
    // sub_71000E13614 passes an explicit 0 for its ignored middle int parameter. Calls, branches
    // and member stores are identical.
    sead::SafeString label;
    sead::SafeString actor_instance;
    bool* is_hide_caption;
    if (getDynamicParam(&label, "Label"))
        mLabel_d = label;
    if (getDynamicParam(&actor_instance, "ActorInstance"))
        mActorInstance_d = actor_instance;
    if (getDynamicParam(&is_hide_caption, "IsHideCaption"))
        mIsHideCaption_d = is_hide_caption;
    sub_71000E13614(&mLabel_d, 0, *mIsHideCaption_d);
}

void DemoVoiceTrigger::leave_() {
    if (!_52)
        ui::UI::instance()->sub_71010A6D84();
}

void DemoVoiceTrigger::loadParams_() {
    getDynamicParam(&mIsHideCaption_d, "IsHideCaption");
    getDynamicParam(&mLabel_d, "Label");
    getDynamicParam(&mActorInstance_d, "ActorInstance");
}

void DemoVoiceTrigger::calc_() {
    if (_50) {
        if (!_52)
            ui::UI::instance()->sub_71010A7034();
        _50 = false;
    }

    if (_52)
        return;

    if (_51 && !_f8.isEnabled()) {
        if (ui::UI::instance()->sub_71010A5BC8())
            ui::UI::instance()->sub_71010A6D84();
    }
}

}  // namespace uking::action
