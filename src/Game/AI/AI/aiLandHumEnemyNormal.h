#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(LandHumEnemyNormal, EnemyNormal)
public:
    explicit LandHumEnemyNormal(const InitArg& arg);
    ~LandHumEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    s32 m52(s32 idx) override;
    s32 m53() override { return 11; }

protected:
    // static_param at offset 0x3d0
    const float* mTerrorIgnoreDist_s{};
    // static_param at offset 0x3d8
    const float* mExplosivesSearchDist_s{};
    // static_param at offset 0x3e0
    const float* mExplosivesSearchSpeed_s{};
    // static_param at offset 0x3e8
    const float* mExplosivesSearchAng_s{};
    ksys::act::BaseProcLink _3f0;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyNormal, 0x400);

}  // namespace uking::ai
