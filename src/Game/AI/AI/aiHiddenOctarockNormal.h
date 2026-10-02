#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenOctarockNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(HiddenOctarockNormal, EnemyNormal)
public:
    explicit HiddenOctarockNormal(const InitArg& arg);
    ~HiddenOctarockNormal() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m49(Unk1* out, s32 idx) override;
    void m37() override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 2; }

    ksys::act::Unk_71024dc858* m47(ksys::act::AwarenessInstance* awareness,
                                   ksys::act::Unk_71024dccf8* filter, s32 a3) override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;
    void m69(Unk2* target) override;
    void m34() override;

    // 0x7100432294: with IsHitGround, the character controller stops colliding with the ground
    // layers.
    void sub_7100432294();
protected:
    // static_param at offset 0x3d0
    const float* mOptionHitReactionDelay_s{};
    // static_param at offset 0x3d8
    const bool* mIsSitDown_s{};
    // static_param at offset 0x3e0
    const bool* mIsHitGround_s{};
    // static_param at offset 0x3e8
    const bool* mIsReactionByWigHit_s{};
    // static_param at offset 0x3f0
    const bool* mIsHide_s{};
    // static_param at offset 0x3f8
    const bool* mIsIvalidateSight_s{};
    // static_param at offset 0x400
    const bool* mIsSealHearing_s{};
    // map_unit_param at offset 0x408
    const bool* mIsNearCreate_m{};
    bool _410 = false;
    f32 _414 = 0;
    s32 _418 = 0;
    s32 _41c = 0;
};
KSYS_CHECK_SIZE_NX150(HiddenOctarockNormal, 0x420);

}  // namespace uking::ai
