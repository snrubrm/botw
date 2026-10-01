#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyHideGrass : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyHideGrass, ksys::act::ai::Ai)
public:
    explicit EnemyHideGrass(const InitArg& arg);
    ~EnemyHideGrass() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSightRatio_s{};
    // static_param at offset 0x40
    const float* mHearingRatio_s{};
    f32 _48 = 1.0f;
    f32 _4c = 1.0f;
};

}  // namespace uking::ai
