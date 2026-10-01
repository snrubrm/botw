#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossThunderSign : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossThunderSign, ksys::act::ai::Action)
public:
    explicit LastBossThunderSign(const InitArg& arg);
    ~LastBossThunderSign() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSignTime_s{};
    float _28 = 0.0f;
    int _2c = 0;
    int _30 = 0;
};

}  // namespace uking::action
