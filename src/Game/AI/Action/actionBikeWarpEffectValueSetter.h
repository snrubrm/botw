#pragma once

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
    float _30 = 0.0f;
    float _34 = 0.0f;
    int _38 = 0;
    float _3c = 1.0f;
};

}  // namespace uking::action
