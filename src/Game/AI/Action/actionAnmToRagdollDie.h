#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmToRagdollDie : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmToRagdollDie, ksys::act::ai::Action)
public:
    explicit AnmToRagdollDie(const InitArg& arg);
    ~AnmToRagdollDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mChangeRagdollFrame_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    // static_param at offset 0x38
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0x48
    sead::SafeString mRagdollControllerName_s{};
    f32 _58 = 0.0f;
    f32 _5c = 1.0f;
    f32 _60 = 0.0f;
    bool _64 = false;
    bool _65 = true;
};

}  // namespace uking::action
