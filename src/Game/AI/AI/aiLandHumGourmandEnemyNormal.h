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
    void m50(Unk1* out, s32 idx) override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 12; }
    void m49(Unk1* out, s32 idx) override;

    bool m56(Unk2* out, Unk1* info) override;
    void m57(s32 type, Unk2* target) override;
    void m58(s32 type, Unk2* target) override;
    void m59() override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;

    void sub_7100472538();
    // 0x71004726b4: whether the bait `link` is unusable.
    bool sub_71004726B4(ksys::act::BaseProcLink* link);
    // 0x71004727cc
    void sub_71004727CC(const ksys::act::BaseProcLink& link);
    // 0x71004728a4
    void changeToFoundBait(Unk2* target);
    // 0x71004729d8
    bool sub_71004729D8(Unk2* out, Unk1* info);
    // 0x7100472ae8: a reachable bait within EatArea (dummy link if none).
    ksys::act::BaseProcLink& sub_7100472AE8();

protected:
    // static_param at offset 0x400
    const int* mRefindBaitTime_s{};
    // static_param at offset 0x408
    const int* mEatArea_s{};
    // static_param at offset 0x410
    const int* mEatNavType_s{};
    ksys::Timer _418{0, 0};
    sead::Vector3f _424{0, 0, 0};
    // aitree_variable at offset 0x430
    void* mTargetBaitActorLink_a{};
    // aitree_variable at offset 0x438
    bool* mIsTrgChangeUnderWaterState_a{};
    Unk_7102370e70 _440;
};
KSYS_CHECK_SIZE_NX150(LandHumGourmandEnemyNormal, 0x458);

}  // namespace uking::ai
