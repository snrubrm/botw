#pragma once

#include <math/seadMatrix.h>
#include <prim/seadEnum.h>
#include "Game/Actor/AI/aiHorseRiddenStatusSelector.h"
#include "Game/Actor/aiFlagByte.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MotorcycleRoot : public HorseRiddenStatusSelector {
    SEAD_RTTI_OVERRIDE(MotorcycleRoot, HorseRiddenStatusSelector)
public:
    explicit MotorcycleRoot(const InitArg& arg);
    ~MotorcycleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    // 0x71004ad5c8 (CSV AI_AI_MotorcycleRoot::x; placeholder name): updates the AS flags 0x2c (energy left),
    // 0x1a (no rider state) and 0x29 (energy empty) of the AS flag parameter 0x42.
    void updateASFlags();

    // Placeholder (bits of _81; the bit index goes through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5)

protected:
    // static_param at offset 0x38
    const float* mInWaterRateForDisappear_s{};
    // static_param at offset 0x40
    const float* mDistanceToPlayerForDisappear_s{};
    // static_param at offset 0x48
    const float* mNoiseEnergyEmpty_s{};
    // static_param at offset 0x50
    const float* mNoiseNotRidden_s{};
    // static_param at offset 0x58
    const float* mNoiseThrottleClose_s{};
    // static_param at offset 0x60
    const float* mNoiseThrottleOpen_s{};
    // static_param at offset 0x68
    const float* mForestFogRatioForDisappear_s{};
    void* _70{};
    sead::Matrix34f* _78{};  // set by message 0x380001d, applied by enter_
    bool _80{};
    FlagByte<Flag> _81;
    u32 _84 = 0;
};

}  // namespace uking::ai
