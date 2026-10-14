#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BikeWarpEffectValueSetter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BikeWarpEffectValueSetter, ksys::act::ai::Action)
public:
    explicit BikeWarpEffectValueSetter(const InitArg& arg);
    ~BikeWarpEffectValueSetter() override;

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

    // 0x71000509c4 (out of line here, inlined into WarpEffectValueSetter): applies the timer ratio to the bike.
    void sub_71000509C4();
};

}  // namespace uking::action
