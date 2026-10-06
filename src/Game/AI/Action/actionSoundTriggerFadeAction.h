#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace xlink2 {
class UserInstance;
}

namespace uking::action {

class SoundTriggerFadeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundTriggerFadeAction, ksys::act::ai::Action)
public:
    explicit SoundTriggerFadeAction(const InitArg& arg);
    ~SoundTriggerFadeAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

    // 0x7100e16b70 (placeholder name): fades the SLink event `mSound_d` of the user instance (false if it is not
    // emitting).
    bool sub_7100E16B70(xlink2::UserInstance* user);

    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
};

}  // namespace uking::action
