#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimidityEnemyDrawback : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TimidityEnemyDrawback, ksys::act::ai::Ai)
public:
    explicit TimidityEnemyDrawback(const InitArg& arg);
    ~TimidityEnemyDrawback() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_71005CA738();

protected:
    // static_param at offset 0x38
    const float* mEscapeDist_s{};
    // static_param at offset 0x40
    const float* mEscapeDistFromHome_s{};
    // static_param at offset 0x48
    const float* mLostRange_s{};
    // static_param at offset 0x50
    const float* mLostVMin_s{};
    // static_param at offset 0x58
    const float* mLostVMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    u32 _68 = 0;
    u32 _6c = 0;
    u32 _70 = 0;
    bool _74 = false;
};
KSYS_CHECK_SIZE_NX150(TimidityEnemyDrawback, 0x78);

}  // namespace uking::ai
