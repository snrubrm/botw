#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagWaterChemical : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagWaterChemical, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTagWaterChemical(const InitArg& arg);
    ~DungeonRotateTagWaterChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710037b08c (placeholder name)
    void changeToDecelerate(f32 ang_vel, f32 ang_accel);
    // 0x710037ae80 (placeholder name)
    void changeToClockwise(f32 ang_vel, f32 ang_accel);
    // 0x710037af84 (placeholder name)
    void changeToCounterClockwise(f32 ang_vel, f32 ang_accel);

protected:
    // static_param at offset 0x38
    const float* mSlowDownRotRadAccel_s{};
    // static_param at offset 0x40
    const float* mSlowDownTimer_s{};
    // static_param at offset 0x48
    const float* mRotRadAccel_s{};
    // static_param at offset 0x50
    const float* mReverseDotTh_s{};
    u8 _58 = 255;
    f32 _5c{};
};

}  // namespace uking::ai
