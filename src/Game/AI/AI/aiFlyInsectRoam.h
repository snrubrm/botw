#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class FlyInsectRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FlyInsectRoam, ksys::act::ai::Ai)
public:
    explicit FlyInsectRoam(const InitArg& arg);
    ~FlyInsectRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003D38B4();
protected:
    // static_param at offset 0x38
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x40
    const float* mTerritoryRadiusRand_s{};
    // static_param at offset 0x48
    const float* mMinHeight_s{};
    // static_param at offset 0x50
    const float* mMaxHeight_s{};
    // static_param at offset 0x58
    const float* mRePathDist_s{};
    // static_param at offset 0x60
    const float* mRePathDistRand_s{};
    // static_param at offset 0x68
    const float* mRePathYDistRand_s{};
    // static_param at offset 0x70
    const float* mMaxRotRand_s{};
    // static_param at offset 0x78
    const float* mMaxRotRandOuter_s{};
    // static_param at offset 0x80
    const bool* mIsEnableOnLand_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _90;
    f32 _9c{};
    bool _a0{};
};

}  // namespace uking::ai
