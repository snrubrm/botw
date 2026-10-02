#pragma once

#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RodEnemyFindPlayer : public LandHumEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(RodEnemyFindPlayer, LandHumEnemyFindPlayer)
public:
    explicit RodEnemyFindPlayer(const InitArg& arg);
    ~RodEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    s32 m53() override { return *mRodWeaponIdx_s; }
    virtual bool m54();

protected:
    // static_param at offset 0x1e8
    const int* mMagicPer_s{};
    // static_param at offset 0x1f0
    const int* mMagicCheckInterval_s{};
    // static_param at offset 0x1f8
    const int* mRodWeaponIdx_s{};
    // static_param at offset 0x200
    const float* mMagicAttackDir_s{};
    // static_param at offset 0x208
    const float* mMagicIntervalIntensity_s{};
    f32 _210 = 0;
};
KSYS_CHECK_SIZE_NX150(RodEnemyFindPlayer, 0x218);

}  // namespace uking::ai
