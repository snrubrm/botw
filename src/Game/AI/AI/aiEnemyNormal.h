#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// Unnamed 0x68-byte heap object owned by EnemyNormal (_48). It has no out-of-line constructor:
// it is constructed inline by EnemyNormal::m65 (0x710039d8f0); placeholder name = that address.
struct Unk_710039D8F0 {
    s32 _0 = -1;
    void* _8 = nullptr;
    sead::Matrix34f _10 = sead::Matrix34f::ident;
    sead::Vector3f _40 = sead::Vector3f::zero;
    bool _4c = false;
    ksys::act::BaseProcLink _50;
    u32 _60 = 0;
};

class EnemyNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNormal, ksys::act::ai::Ai)
public:
    // Attack candidate filled by m49/m50 (stack object of the attack selection at 0x710039ef24:
    // initialised to {-1, 0, 0}); placeholder.
    struct Unk1 {
        s32 _0 = -1;
        s32 _4 = 0;
        u16 _8 = 0;
    };

    explicit EnemyNormal(const InitArg& arg);
    ~EnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual bool m44() { return true; }
    virtual bool m45(const sead::Vector3f& target_pos, const ksys::act::BaseProcLink& target,
                     bool skip_own_pos);
    virtual bool m46(const sead::Vector3f& pos, const ksys::act::BaseProcLink& target);
    virtual void m47();
    virtual void m48(sead::Vector3f* pos);
    virtual void m49(Unk1* out, s32 idx);
    virtual void m50(Unk1* out, s32 idx);
    virtual void m51();
    virtual s32 m52(s32 idx);
    virtual s32 m53() { return 9; }
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual bool m63() { return false; }
    virtual void m64();
    virtual bool m65(sead::Heap* heap);
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual bool m70();
    virtual void m71();
    virtual void m72();
    virtual bool m73();

    void sub_71003A19AC();
protected:
    // aitree_variable at offset 0x38
    int* mPlayerSoundSealRefCount_a{};
    // aitree_variable at offset 0x40
    int* mSealNoPlayerAwnRequestCount_a{};
    Unk_710039D8F0* _48 = nullptr;
    ksys::act::BaseProcLink _50;
    sead::Vector3f _60;
    u32 _6c;
    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
    // static_param at offset 0x78
    const int* mSoundLostTimer_s{};
    // static_param at offset 0x80
    const int* mNoActionReactTimeMin_s{};
    // static_param at offset 0x88
    const int* mNoActionReactTimeMax_s{};
    // static_param at offset 0x90
    const float* mTerritoryArea_s{};
    // static_param at offset 0x98
    const float* mNpcTerritoryArea_s{};
    // static_param at offset 0xa0
    const float* mNoPlayerTerritoryArea_s{};
    // static_param at offset 0xa8
    const float* mSpreadDist_s{};
    // static_param at offset 0xb0
    const float* mEnlargeAwnRatio_s{};
    // static_param at offset 0xb8
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0xc0
    const float* mSpeadDist2_s{};
    // static_param at offset 0xc8
    const float* mHomePosRadius_s{};
    // static_param at offset 0xd0
    const float* mSubsTerritoryArea_s{};
    // static_param at offset 0xd8
    const float* mLostExtinguishFireDist_s{};
    // static_param at offset 0xe0
    const float* mShortRangeTerritoryArea_s{};
    // static_param at offset 0xe8
    const float* mCloseRangeTerritoryArea_s{};
    // static_param at offset 0xf0
    const float* mPressBreakObject_s{};
    // static_param at offset 0xf8
    const float* mTerritoryHeight_s{};
    // static_param at offset 0x100
    const bool* mIsMindDoubtTarget_s{};
    // static_param at offset 0x108
    sead::SafeString mFortressTag_s{};
    // map_unit_param at offset 0x118
    const float* mTerritoryArea_m{};
    f32 _120 = 0;
    s32 _124 = 0;
    s32 _128 = 0;
    bool _12c = false;
    Unk_710235abc8 _130{mActor, 0x8000006};
    Unk_7102450528 _188;
    Unk_71024507f8 _200;
    Unk_71023e8ff8 _290;
    Unk_71023e8fd0 _2e0{mActor, 0x80000c0};
    Unk_71023e9028 _308;
    ksys::Timer _358;
    u32 _364 = 0;
    f32 _368 = 0;
    f32 _36c = 0;
    f32 _370 = 0;
    u8 _374[0x390 - 0x374];
    ksys::act::BaseProcLink _390;
    sead::Vector3f _3a0;
    sead::BitFlag32 _3ac;
    const float* _3b0 = nullptr;
    f32 _3b8 = 0;
    u32 _3bc;
    ksys::act::BaseProcLink _3c0;
};
KSYS_CHECK_SIZE_NX150(EnemyNormal, 0x3d0);

}  // namespace uking::ai
