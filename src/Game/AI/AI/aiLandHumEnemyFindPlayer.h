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
    bool m48() override;
    bool m49() override;
    bool m50() override;
    bool m51() override;
    bool m52() override;
    virtual s32 m53() { return *mWeaponIdx_s; }

    // 0x710046096c / 0x7100460ee8 / 0x7100461020 (not decompiled; used by enter_)
    bool sub_710046096C();
    void sub_7100460EE8();
    void sub_7100461020();
    // 0x7100461b74: whether the player (while hanging or in the 21 state) is within the climb
    // height range (ClimbVmin..ClimbVmax) and horizontal distance (ClimbHmax) of the actor.
    bool sub_7100461B74();
    // inline-only in the original; name is a guess (sub_7100460EE8, sub_7100461020 and m44 repeat it):
    // the translation of the actor linked by _1c8.
    void getChemTargetPos(sead::Vector3f* pos);
    // 0x7100461c98: _1dc = 15, then the child "対象壁つかまり" with TargetPos = the enemy target position.
    void sub_7100461C98();

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
    f32 _1dc = 0;
    bool _1e0 = false;
    bool _1e1 = false;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyFindPlayer, 0x1e8);

}  // namespace uking::ai
