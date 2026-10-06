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

protected:
    void calc_() override;

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
