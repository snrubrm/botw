#pragma once

#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GearRangeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GearRangeSelect, ksys::act::ai::Ai)
public:
    explicit GearRangeSelect(const InitArg& arg);
    ~GearRangeSelect() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Gear value of the rideable and the "GearThreashold" parameter (SEAD_ENUMs in the original: both
    // values go through a stack round trip); the names and the number of values are guesses.
    SEAD_ENUM(Gear, _0, _1, _2, _3, _4, _5, _6, _7)

    // static_param at offset 0x38
    const int* mGearThreashold_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
};

}  // namespace uking::ai
