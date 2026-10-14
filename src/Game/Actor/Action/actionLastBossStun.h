#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossStun : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossStun, ksys::act::ai::Action)
public:
    explicit LastBossStun(const InitArg& arg);
    ~LastBossStun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mStunTime_s{};
    // static_param at offset 0x28
    const float* mAddStunTime_s{};
    // static_param at offset 0x30
    const float* mShockWaveDownTime_s{};
    int _38 = 0;
    float _3c = 0.0f;
    float _40 = 0.0f;
    int _44 = 0;
    u8 _48[0x88 - 0x48];
};

}  // namespace uking::action
