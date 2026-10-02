#pragma once

#include <prim/seadBitFlag.h>
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
    // Result of the unnamed enemy helper 0x71005e2bcc (type unknown).
    void* _f0 = nullptr;
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
