#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class LandHumEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(LandHumEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit LandHumEnemyFindPlayer(const InitArg& arg);
    ~LandHumEnemyFindPlayer() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    // 0x7100461158 (not decompiled yet)
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100462930 (not decompiled yet)
    void m40() override;

    void m44() override;
    bool m43() override;
    virtual s32 m53() { return *mWeaponIdx_s; }

    // 0x710046096c / 0x7100460ee8 / 0x7100461020 (not decompiled; used by enter_)
    bool sub_710046096C();
    void sub_7100460EE8();
    void sub_7100461020();

protected:
    // static_param at offset 0x140
    const int* mThrowWeaponPer_s{};
    // static_param at offset 0x148
    const int* mNoChemSearchWpIdx_s{};
    // static_param at offset 0x150
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0x158
    const float* mExplosivesAvoidSpeed_s{};
    // static_param at offset 0x160
    const float* mExplosivesAvoidAng_s{};
    // static_param at offset 0x168
    const float* mChemicalSearchDist_s{};
    // static_param at offset 0x170
    const float* mNoSearchDist_s{};
    // static_param at offset 0x178
    const float* mVoltage_s{};
    // static_param at offset 0x180
    const float* mChemicalActionDist_s{};
    // static_param at offset 0x188
    const float* mThrowWeaponDist_s{};
    // static_param at offset 0x190
    const float* mNoBurnWaterDepth_s{};
    // static_param at offset 0x198
    const float* mNearScaffoldDist_s{};
    // static_param at offset 0x1a0
    const float* mClimbVmin_s{};
    // static_param at offset 0x1a8
    const float* mClimbVmax_s{};
    // static_param at offset 0x1b0
    const float* mClimbHmax_s{};
    ksys::act::BaseProcLink _1b8;
    ksys::act::BaseProcLink _1c8;
    f32 _1d8 = 0;
    u32 _1dc = 0;
    bool _1e0 = false;
    bool _1e1 = false;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyFindPlayer, 0x1e8);

}  // namespace uking::ai
