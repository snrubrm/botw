#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// vtable 0x7102424170: damage callback embedded in StalEnemyRoot (no RTTI of its own).
class Unk_7102424170 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;

    bool _24 = false;
};

// vtable 0x71024241a8: the object StalEnemyRoot shares through the "StalEnemyUnit" AI tree variable.
class Unk_71024241a8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71024241a8, Unk_71025afb58)
public:
    sead::BitFlag8 _8;
    f32 _c = 80.0f;
    f32 _10 = 160.0f;
    f32 _14 = 60.0f;
};

class StalEnemyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyRoot, ksys::act::ai::Ai)
public:
    explicit StalEnemyRoot(const InitArg& arg);
    ~StalEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual bool m34();
    virtual void m35(ksys::act::ai::InlineParamPack* params);
    virtual bool m36();

protected:
    Unk_7102424170 _38;
    Unk_7100702370* _60{};
    // static_param at offset 0x68
    const int* mDeadCount_s{};
    // static_param at offset 0x70
    const float* mSearchFrame_s{};
    // static_param at offset 0x78
    const float* mInWaterDepth_s{};
    // static_param at offset 0x80
    const float* mOutOfWaterOffset_s{};
    // static_param at offset 0x88
    const float* mDeadCheckFrame_s{};
    // static_param at offset 0x90
    const float* mSpreadDist_s{};
    // static_param at offset 0x98
    const float* mSmallSpreadDist_s{};
    // static_param at offset 0xa0
    const float* mSearchDistXZ_s{};
    // static_param at offset 0xa8
    const float* mSearchDistY_s{};
    // static_param at offset 0xb0
    const float* mFallHeight_s{};
    // map_unit_param at offset 0xb8
    const bool* mIsCreateStalPart_m{};
    // aitree_variable at offset 0xc0
    bool* mIsStopFallCheck_a{};
    // aitree_variable at offset 0xc8
    void* mStalEnemyUnit_a{};
    Unk_710236f520 _d0{mActor, 0x8000007};
    Unk_7102450b88 _100;
    Unk_71024507c8 _150{0x1800004};
    Unk_71023eaec8 _190{mActor, 0x8000017};
    ksys::Timer _200{0, 0};
    ksys::Timer _20c{0, 0};
    u32 _218 = 0;
    ksys::act::BaseProcLink _220;
    sead::FixedSafeString<64> _230;
    sead::FixedSafeString<64> _288;
    bool _2e0 = false;
    Unk_71024241a8 _2e8;
};
KSYS_CHECK_SIZE_NX150(StalEnemyRoot, 0x300);

}  // namespace uking::ai
