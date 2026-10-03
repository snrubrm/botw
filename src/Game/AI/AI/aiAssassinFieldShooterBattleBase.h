#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinFieldShooterBattleBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinFieldShooterBattleBase, ksys::act::ai::Ai)
public:
    explicit AssassinFieldShooterBattleBase(const InitArg& arg);
    ~AssassinFieldShooterBattleBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    // 0x710032276c: whether the target is further than WarpDistFar / nearer than WarpDistNear (XZ) from
    // the actor, with a ground check below the target; names are guesses.
    bool sub_710032276C();
    // 0x7100322560: whether the shooter should give up / warp (the delay ran out, the actor or its
    // target is on non-auto-placement ground, or the target is further than TerritoryDist from the
    // home position); name is a guess.
    bool sub_7100322560();
    // 0x71003228dc: whether the weapon `*mWeaponIdx_s` check passes and the enemy's attack-interval
    // timer has run out.
    bool sub_71003228DC();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mTiredTime_s{};
    // static_param at offset 0x48
    const float* mWarpDistNear_s{};
    // static_param at offset 0x50
    const float* mWarpDistFar_s{};
    // static_param at offset 0x58
    const float* mTerritoryDist_s{};
    // static_param at offset 0x60
    const float* mTiredGrHeight_s{};
    // static_param at offset 0x68
    const float* mIntervalIntensity_s{};
    f32 _70{};
    s32 _74{};
    s32 _78{};
};
KSYS_CHECK_SIZE_NX150(AssassinFieldShooterBattleBase, 0x80);

}  // namespace uking::ai
