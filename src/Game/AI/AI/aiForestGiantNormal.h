#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(ForestGiantNormal, EnemyNormal)
public:
    explicit ForestGiantNormal(const InitArg& arg);
    ~ForestGiantNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // static_param at offset 0x3d0
    const float* mSleepingHearAwnRatio_s{};
    bool _3d8 = false;
    f32 _3dc = 0;
    s32 _3e0 = 0;
    s32 _3e4 = 0;
};
KSYS_CHECK_SIZE_NX150(ForestGiantNormal, 0x3e8);

}  // namespace uking::ai
