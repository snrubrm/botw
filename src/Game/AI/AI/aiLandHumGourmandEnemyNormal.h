#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumGourmandEnemyNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(LandHumGourmandEnemyNormal, LandHumEnemyNormal)
public:
    explicit LandHumGourmandEnemyNormal(const InitArg& arg);
    ~LandHumGourmandEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35() override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 12; }

    void sub_7100472538();

protected:
    // static_param at offset 0x400
    const int* mRefindBaitTime_s{};
    // static_param at offset 0x408
    const int* mEatArea_s{};
    // static_param at offset 0x410
    const int* mEatNavType_s{};
    ksys::Timer _418{0, 0};
    u32 _424 = 0;
    u32 _428 = 0;
    u32 _42c = 0;
    // aitree_variable at offset 0x430
    void* mTargetBaitActorLink_a{};
    // aitree_variable at offset 0x438
    bool* mIsTrgChangeUnderWaterState_a{};
    Unk_7102370e70 _440;
};
KSYS_CHECK_SIZE_NX150(LandHumGourmandEnemyNormal, 0x458);

}  // namespace uking::ai
