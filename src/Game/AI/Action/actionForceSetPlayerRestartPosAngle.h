#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceSetPlayerRestartPosAngle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceSetPlayerRestartPosAngle, ksys::act::ai::Action)
public:
    explicit ForceSetPlayerRestartPosAngle(const InitArg& arg);
    ~ForceSetPlayerRestartPosAngle() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;
    bool oneShot_() override;

protected:
    // 0x7100138d68: out-of-line implementation; map search owner remains unresolved.
    void sub_7100138D68();

    // dynamic_param at offset 0x20
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mAnchorName_d{};
};

}  // namespace uking::action
