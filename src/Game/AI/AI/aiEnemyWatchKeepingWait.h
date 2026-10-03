#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWatchKeepingWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyWatchKeepingWait, ksys::act::ai::Ai)
public:
    explicit EnemyWatchKeepingWait(const InitArg& arg);
    ~EnemyWatchKeepingWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x71003c5ef4 (placeholder name)
    void changeToWait();

protected:
    f32 _38 = 0;
    // static_param at offset 0x40
    const int* mIdleCheckMin_s{};
    // static_param at offset 0x48
    const int* mIdleCheckMax_s{};
    // static_param at offset 0x50
    const int* mIdlePer_s{};
    // map_unit_param at offset 0x58
    const float* mRotAngle_m{};
    // map_unit_param at offset 0x60
    const float* mWaitTime_m{};
    f32 _68{};
    s32 _6c{};
    s32 _70{};
    bool _74{};
    f32 _78 = 0;
    bool _7c = true;
    bool _7d = false;
    bool _7e = false;
};

}  // namespace uking::ai
