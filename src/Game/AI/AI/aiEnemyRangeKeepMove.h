#pragma once

#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRangeKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRangeKeepMove, ksys::act::ai::Ai)
public:
    explicit EnemyRangeKeepMove(const InitArg& arg);
    ~EnemyRangeKeepMove() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual int m35() { return *mWeaponIdx_s; }
    virtual void m36() {}
    virtual void m37() {}
    virtual void m38() {}
    virtual void m39() { m38(); }
    virtual void m40() {}

    void sub_71003AB3FC();
    void changeToBattleBackAway();
    void changeToBattleWait();
    bool sub_71003AD058();
    bool sub_71003AD160();
    bool sub_71003AD1F8();
    bool sub_71003AD298();
    // 0x71003ab624 (placeholder name)
    void changeToBattleWalk();
    // 0x71003acd3c (placeholder name)
    void changeToForcedRetreat();
    // 0x71003abe3c (placeholder name)
    void changeToMoveSideways(s8 dir);

protected:
    // aitree_variable at offset 0x38
    void* mRefPosVibrateCheckerForAI_a{};
    // aitree_variable at offset 0x40
    void* mRefVelRotVibrateCheckerforAI_a{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const int* mBackTimeMin_s{};
    // static_param at offset 0x58
    const int* mBackTimeMax_s{};
    // static_param at offset 0x60
    const int* mLeaveTimerMin_s{};
    // static_param at offset 0x68
    const int* mLeaveTimerMax_s{};
    // static_param at offset 0x70
    const int* mPosVibrateFrame_s{};
    // static_param at offset 0x78
    const int* mRotVelVibrateFrame_s{};
    // static_param at offset 0x80
    const float* mCloseDist_s{};
    // static_param at offset 0x88
    const float* mFarDist_s{};
    // static_param at offset 0x90
    const float* mOutDist_s{};
    // static_param at offset 0x98
    const float* mBaseDist_s{};
    // static_param at offset 0xa0
    const float* mSpaceDist_s{};
    // static_param at offset 0xa8
    const float* mSpaceAngle_s{};
    // static_param at offset 0xb0
    const bool* mIsCheckBack_s{};
    // static_param at offset 0xb8
    const bool* mIsCheckReachable_s{};
    // static_param at offset 0xc0
    const float* mNoMoveDist_s{};
    f32 _c8{};
    s32 _cc{};
    s32 _d0{};
    f32 _d4{};
    s32 _d8{};
    s32 _dc{};
    f32 _e0{};
    s32 _e4{};
    s32 _e8{};
    // Vibrate checker holders (see mRefPosVibrateCheckerForAI_a / mRefVelRotVibrateCheckerforAI_a)
    Unk_71000b0800<Unk_71025b0578> _f0;
    Unk_71000b0800<Unk_71025b7688> _f8;
    sead::Vector3f _100 = sead::Vector3f::zero;
    bool _10c{};
    bool _10d{};
};

}  // namespace uking::ai
