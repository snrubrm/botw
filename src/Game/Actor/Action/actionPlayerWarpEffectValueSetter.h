#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWarpEffectValueSetter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerWarpEffectValueSetter, ksys::act::ai::Action)
public:
    explicit PlayerWarpEffectValueSetter(const InitArg& arg);
    ~PlayerWarpEffectValueSetter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mChangeType_d{};
    // dynamic_param at offset 0x28
    float* mSetFrame_d{};
    ksys::Timer _30{0.0f, 0.0f, 0.0f};
    float _3c = 1.0f;
};

}  // namespace uking::action
