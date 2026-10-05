#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

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
    void sub_710050BB0C();

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
    s32 _b0 = 4;
    ksys::Timer _b4{0, 0};
    sead::Vector3f _c0;
    sead::Vector3f _cc;
    u64 _d8 = 0;
    u32 _e0 = 0;
    s32 _e4 = -1;
    sead::SafeArray<u32, 13> _e8{};  // indexed by a SEAD_ENUM
    void* _120 = nullptr;  // heap object freed by the destructor
    s32 _128 = 2;
    s32 _12c = 2;
    u64 _130 = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossActorNormalMode, 0x138);

}  // namespace uking::ai
