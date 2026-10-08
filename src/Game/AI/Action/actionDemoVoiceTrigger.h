#pragma once

#include <aal/aalHandle.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace aal {
class Emitter;
}

namespace uking::action {

class DemoVoiceTrigger : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoVoiceTrigger, ksys::act::ai::Action)
public:
    explicit DemoVoiceTrigger(const InitArg& arg);
    ~DemoVoiceTrigger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71000e13614 (declared only): starts the voice for the label (sets _52 etc.).
    // The middle int parameter is ignored by the callee (x2 is overwritten before any read);
    // our call passes 0, costing one extra mov.
    void sub_71000E13614(const sead::SafeString* label, int unused, bool hide_caption);

protected:
    void calc_() override;

    // 0x7100e13474 (placeholder name): the init_ body (emitter allocation, _50 = false) without the return value.
    void sub_7100E13474(sead::Heap* heap);

    // dynamic_param at offset 0x20
    bool* mIsHideCaption_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mLabel_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mActorInstance_d{};
    aal::Emitter* mEmitter = nullptr;
    bool _50 = false;
    bool _51 = false;
    bool _52 = false;
    u8 _53[0xf8 - 0x53];
    aal::Handle _f8;
};

}  // namespace uking::action
