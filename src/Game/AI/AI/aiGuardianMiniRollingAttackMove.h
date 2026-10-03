#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace uking::ai {

class GuardianMiniRollingAttackMove;

// vtable 0x71023f92d8: damage callback without RTTI of its own (call 0x71004256a0, not decompiled yet).
class Unk_71023f92d8 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    GuardianMiniRollingAttackMove* _28{};
};

// vtable 0x71023f9310: damage callback without RTTI of its own (call 0x7100425c88, not decompiled yet).
class Unk_71023f9310 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    GuardianMiniRollingAttackMove* _28{};
};

class GuardianMiniRollingAttackMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(GuardianMiniRollingAttackMove, EnemyRangeKeepMove)
public:
    explicit GuardianMiniRollingAttackMove(const InitArg& arg);
    ~GuardianMiniRollingAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    int m35() override;
    void m36() override;
    void m37() override;
    void m38() override;
    void m40() override;
    bool handleMessage_(const ksys::Message& message) override;

    // 0x71004238f0 ("バックステップ" start), 0x7100423a1c (partial bones + attack AS), 0x7100423d68 /
    // 0x7100423f0c / 0x7100424080 (states "回転待機" / "回転後退" / "回転待機"), 0x7100424554 /
    // 0x7100424670 / 0x7100424a3c (weapon requests). Placeholder names.
    void sub_71004219B8();
    void sub_71004238F0();
    void sub_7100423A1C();
    void sub_7100423D68();
    void sub_7100423F0C();
    void sub_7100424080();
    void sub_7100424554();
    void sub_7100424670();
    void sub_7100424A3C();
    // 0x7100424f54 (changeChild "回転終了") / 0x7100425040 (changeChild "チャンス").
    void sub_7100424F54();
    void sub_7100425040();

    // 0x7100421b50: sends the weapon request type 1 (default arguments) to the weapons 0 - 2 of the actor.
    void sub_7100421B50();

protected:
    // static_param at offset 0x110
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x120
    sead::SafeString mAttackNodeName_s{};
    // static_param at offset 0x130
    sead::SafeString mAttackASName_s{};
    // static_param at offset 0x140
    const int* mRollingNumMin_s{};
    // static_param at offset 0x148
    const int* mRollingNumMax_s{};
    // static_param at offset 0x150
    const int* mRollingWaitTime_s{};
    // static_param at offset 0x158
    const int* mRollingIntervalTime_s{};
    // static_param at offset 0x160
    const int* mStopRollingNum_s{};
    // static_param at offset 0x168
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x170
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x178
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x180
    const float* mRotSpeed_s{};
    // static_param at offset 0x188
    const float* mBackWalkRotSpeedRatio_s{};
    // static_param at offset 0x190
    const float* mRushRotSpeedRatio_s{};
    // static_param at offset 0x198
    const int* mAttackType_s{};
    // static_param at offset 0x1a0
    const int* mBackWalkMinTime_s{};
    // static_param at offset 0x1a8
    const int* mBackWalkRollingStartTime_s{};
    // static_param at offset 0x1b0
    const float* mBackWalkDist_s{};
    // static_param at offset 0x1b8
    const int* mRushAttackImpulse_s{};
    // static_param at offset 0x1c0
    const int* mRollingStopTime_s{};
    // static_param at offset 0x1c8
    const bool* mIsValidChanceTime_s{};
    // static_param at offset 0x1d0
    const int* mCrashDamage_s{};
    // static_param at offset 0x1d8
    const int* mBreakPillarTime_s{};

    /* 0x1e0 */ ksys::Timer _1e0{0.0f, 0.0f};
    /* 0x1ec */ ksys::Timer _1ec{0.0f, 0.0f};
    /* 0x1f8 */ ksys::Timer _1f8{0.0f, 0.0f};
    /* 0x204 */ ksys::Timer _204{0.0f, 0.0f};
    /* 0x210 */ ksys::Timer _210{0.0f, 0.0f};
    /* 0x21c */ ksys::Timer _21c{0.0f, 0.0f};
    /* 0x228 */ u8 _228 = 0;
    /* 0x229 */ u8 _229 = 0;
    /* 0x22a */ bool _22a = false;
    /* 0x22c */ sead::Vector3f _22c{};
    /* 0x238 */ sead::Vector3f _238{};
    /* 0x244 */ f32 _244 = 0.0f;
    /* 0x248 */ f32 _248 = 0.0f;
    /* 0x24c */ f32 _24c = 0.0f;
    /* 0x250 */ Unk_71023f83e8* _250{};
    /* 0x258 */ Unk_7102450498 _258;
    /* 0x2a8 */ Unk_71012419b4 _2a8{};
    /* 0x2c8 */ u8 _2c8 = 0;
    /* 0x2c9 */ u8 _2c9 = 0;
    /* 0x2d0 */ Unk_7102451ba0 _2d0;
    /* 0x2f8 */ Unk_71023f92d8 _2f8;
    /* 0x328 */ Unk_71023f9310 _328;
    /* 0x358 */ bool _358 = false;
};
static_assert(sizeof(GuardianMiniRollingAttackMove) == 0x360, "");

}  // namespace uking::ai
