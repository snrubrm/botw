#pragma once

#include <prim/seadBitFlag.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class EnemyBaseFindPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBaseFindPlayer, ksys::act::ai::Ai)
public:
    explicit EnemyBaseFindPlayer(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual f32 m34();
    virtual bool m35();
    virtual bool m36(bool b);
    virtual bool m37();
    virtual bool m38();
    virtual bool m39(const sead::Vector3f& pos, bool b);
    virtual void m40();
    virtual void m41();
    virtual bool m42(s32 x);
    virtual bool m43();
    virtual void m44();
    virtual bool m45() { return isCurrentChild("威嚇"); }
    virtual bool m46() { return true; }
    virtual void m47();
    virtual bool m48() { return false; }
    virtual bool m49() { return false; }
    virtual bool m50() { return false; }
    virtual bool m51() { return false; }
    virtual bool m52() { return false; }

    // 0x710037e9a4: picks the lost timer range (LostTimer .. LostTimer * 1.1) and a random value.
    void sub_710037E9A4();
    // 0x710037ecd0: TargetPos → ナビメッシュ無し.
    void sub_710037ECD0();
    // 0x710037eda4: new random lost timer value; TargetPos (sub_71005D98D8) → 気づき.
    void sub_710037EDA4();
    // 0x710037eeac
    bool sub_710037EEAC();
    // 0x71003804f4
    bool sub_71003804F4();
    // 0x71003803e8: surprise attack timer, lost timer, then sub_710037EDA4.
    void sub_71003803E8();
    // 0x710038054c: new random timers (_f8, _120); TargetPos + CentralPos (home) → 威嚇帰還.
    void sub_710038054C();
    // 0x7100380b50: whether a swift attack (速攻) is possible: target height difference within
    // SwiftAttackVMin..Max, target not x_13() (player accessor), EnemyLevel IsSwiftAttack.
    bool sub_7100380B50();
    // 0x710037ef30 (not decompiled; tail-called by enter_)
    void sub_710037EF30();
    // 0x71003806c8 (not decompiled; called by sub_710037EF30)
    void sub_71003806C8();
    // 0x7100380e90: TargetPos → 不意討ち.
    void sub_7100380E90();

protected:
    // static_param at offset 0x38
    const int* mSurpriseAttackPer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const int* mLostTimer_s{};
    // static_param at offset 0x50
    const int* mSurpriseAttackTime_s{};
    // static_param at offset 0x58
    const int* mSurpriseAttackTimeRand_s{};
    // static_param at offset 0x60
    const int* mRerouteTimeMin_s{};
    // static_param at offset 0x68
    const int* mRerouteTimeMax_s{};
    // static_param at offset 0x70
    const int* mRestreintTime_s{};
    // static_param at offset 0x78
    const int* mRetTiredFromTime_s{};
    // static_param at offset 0x80
    const float* mSurpriseAttackRange_s{};
    // static_param at offset 0x88
    const float* mAttackRange_s{};
    // static_param at offset 0x90
    const float* mAttackVMin_s{};
    // static_param at offset 0x98
    const float* mAttackVMax_s{};
    // static_param at offset 0xa0
    const float* mSwiftAttackVMin_s{};
    // static_param at offset 0xa8
    const float* mSwiftAttackVMax_s{};
    // static_param at offset 0xb0
    const float* mRestreintTiredDist_s{};
    // static_param at offset 0xb8
    const float* mForceFirstAttackDist_s{};
    // static_param at offset 0xc0
    const float* mRetForceFirstAttackDist_s{};
    // static_param at offset 0xc8
    const float* mPathTooLongDist_s{};
    // static_param at offset 0xd0
    const float* mNoSearchFromTiredDist_s{};
    // aitree_variable at offset 0xd8
    bool* mIsTryingReturnRestreint_a{};
    f32 _e0{};
    f32 _e4{};
    sead::BitFlag32 _e8;
    // Result of sub_71005E2BCC.
    act::Enemy::Unk_12d0* _f0 = nullptr;
    f32 _f8 = 0;
    s32 _fc = 0;
    s32 _100 = 0;
    // Float counter advanced by the delta frame (m44 calls 0x7100d3bc4c on it; init_ sets its value).
    ksys::act::Unk_7100d3bc4c _108{mActor};
    s32 _118 = 0;
    s32 _11c = 0;
    f32 _120 = 0;
    s32 _124 = 0;
    s32 _128 = 0;
    f32 _12c = 0;
    sead::Vector3f _130{-100000.0f, 0, 0};
};
KSYS_CHECK_SIZE_NX150(EnemyBaseFindPlayer, 0x140);

}  // namespace uking::ai
