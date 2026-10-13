#include "Game/AI/Action/actionDemoVoiceTrigger.h"
#include <aal/aalArbiter.h>
#include <aal/aalSystemAccessor.h>
#include <devenv/seadEnvUtil.h>
#include "Game/UI/uiUI.h"

namespace uking::action {

bool Unk_71024e0d08::sub_7100BA1AEC(sead::BufferedSafeString* path, aal::AssetInfo* info) {
    if (!path || !info)
        return false;
    path->clear();
    const char* language = sead::EnvUtil::getRegionLanguage().text();
    path->appendWithFormat("Voice/%s/%s/%s%s", language, _8.cstr(), info->getAssetName(), ".bfstm");
    return true;
}

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

void DemoVoiceTrigger::sub_7100E13474(sead::Heap* heap) {
    mEmitter = aal::SystemAccessor::getArbiter()->allocEmitter(heap, "demoVoiceTrigger");
    _50 = false;
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

void DemoVoiceTrigger::sub_7100E13B18(const aal::MarkerController::MarkerCallbackInfo& info,
                                    void* user_data) {
    const sead::SafeString marker(info.name);
    sead::SafeString language(sead::EnvUtil::getRegionLanguage().text());
    switch (sead::EnvUtil::getRegionLanguage().value()) {
    case sead::RegionLanguageID::KRko:
    case sead::RegionLanguageID::CNzh:
    case sead::RegionLanguageID::TWzh:
        language = sead::RegionLanguageID::text(sead::RegionLanguageID::JPja);
        break;
    default:
        break;
    }
    if (marker.findIndex(language) != -1 || marker == "PageBreak")
        static_cast<DemoVoiceTrigger*>(user_data)->_50 = true;
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
