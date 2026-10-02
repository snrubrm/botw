#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeObstacleCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RangeObstacleCheck, ksys::act::ai::Ai)
public:
    explicit RangeObstacleCheck(const InitArg& arg);
    ~RangeObstacleCheck() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mRangeDist_s{};
    // static_param at offset 0x48
    const float* mHeightMin_s{};
    // static_param at offset 0x50
    const float* mHeightMax_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    u32 _60 = 0;
    u32 _64 = 0;
    u32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(RangeObstacleCheck, 0x70);

}  // namespace uking::ai
