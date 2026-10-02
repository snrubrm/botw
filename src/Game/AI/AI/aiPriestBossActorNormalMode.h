#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorNormalMode : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossActorNormalMode, PriestBossMode)
public:
    explicit PriestBossActorNormalMode(const InitArg& arg);
    ~PriestBossActorNormalMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual f32 m35();
    virtual f32 m36();
    virtual f32 m37();
    virtual f32 m38();
    virtual f32 m39();
    virtual f32 m40();
    virtual f32 m41();
    virtual f32 m42();
    virtual f32 m43();
    virtual f32 m44();
    virtual f32 m45();
    virtual f32 m46();

protected:
    // static_param at offset 0x40
    const int* mApproachWarpRate_s{};
    // static_param at offset 0x48
    const float* mApproachStartDistance_s{};
    // static_param at offset 0x50
    const float* mLeaveStartDistance_s{};
    // static_param at offset 0x58
    const float* mLeaveStartTime_s{};
    // static_param at offset 0x60
    const float* mWaitMinTime_s{};
    // static_param at offset 0x68
    const float* mWaitMaxTime_s{};
    // static_param at offset 0x70
    const float* mSecondHalfLifePercent_s{};
    // static_param at offset 0x78
    const float* mFramesRestrictEarthRelease_s{};
    // static_param at offset 0x80
    const float* mWarpPosDistFromPlayer_s{};
    // static_param at offset 0x88
    const float* mStageMarginRateForEarthRelease_s{};
    // static_param at offset 0x90
    const bool* mIsManagedBtlMgr_s{};
    // dynamic_param at offset 0x98
    bool* mFromSyncMode_d{};
    // aitree_variable at offset 0xa0
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0xa8
    bool* mReturnFromBananaMode_a{};
};

}  // namespace uking::ai
