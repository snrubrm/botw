#pragma once

#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossShootNormalArrowRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossShootNormalArrowRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossShootNormalArrowRoot(const InitArg& arg);
    ~SiteBossShootNormalArrowRoot() override;
    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual void m35();
    virtual void m36(bool a1);
    virtual void m37();
    virtual void m38(bool a1, bool a2);
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual s32 m43();
    virtual s32 m44();
    virtual void m45(sead::Vector3f* out);
    virtual void m46(sead::Vector3f* out);
    virtual bool m47();
    virtual bool m48();
    // 0x710058823c (4.9 KB, not decompiled; the argument is read as a position).
    virtual void m49(const sead::Vector3f& pos);
    // 0x71005879f4: SiteBoss `_1560` method 0x710066dabc(proc, idx) (not decompiled).
    virtual void m50(ksys::act::BaseProc* proc, s32 idx);
    // Slots 51..52 (and 53 in SiteBossReflectArrowRoot) are not declared yet (types unknown).

    bool sub_7100588164(bool a1);

protected:
    // static_param at offset 0x38
    const int* mArrowNum_s{};
    // static_param at offset 0x40
    const int* mAtMinDamage_s{};
    // static_param at offset 0x48
    const int* mAttackPower_s{};
    // static_param at offset 0x50
    const int* mAddAttackPower_s{};
    // static_param at offset 0x58
    const int* mAvoidCountMax_s{};
    // static_param at offset 0x60
    const int* mSeqAvoidRate_s{};
    // static_param at offset 0x68
    const int* mUpDownAvoidRate_s{};
    // static_param at offset 0x70
    const float* mHoldTime_s{};
    // static_param at offset 0x78
    const float* mInitHoldTime_s{};
    // static_param at offset 0x80
    const float* mAvoidLifeRate_s{};
    // static_param at offset 0x88
    const float* mAvoidAngle_s{};
    // static_param at offset 0x90
    const float* mAvoidDist_s{};
    // static_param at offset 0x98
    const float* mAvoidDistRand_s{};
    // static_param at offset 0xa0
    const float* mAvoidWaitCount_s{};
    // static_param at offset 0xa8
    const float* mAvoidWaitCountRand_s{};
    // static_param at offset 0xb0
    const float* mKeepDistance_s{};
    // static_param at offset 0xb8
    const float* mTrigEventAtHold_s{};
    // static_param at offset 0xc0
    const float* mSpineControlOffsetAngleLR_s{};
    // static_param at offset 0xc8
    const float* mSpineControlOffsetAngleUD_s{};
    // static_param at offset 0xd0
    const bool* mIsFinishAtNoDevice_s{};
    // static_param at offset 0xd8
    const bool* mIsIgnoreCancelAttack_s{};
    // static_param at offset 0xe0
    const bool* mIsKeepDistance_s{};
    // static_param at offset 0xe8
    sead::SafeString mArrowName_s{};
    // static_param at offset 0xf8
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0x100
    const sead::Vector3f* mChaseDistOffset_s{};
    // static_param at offset 0x108
    const sead::Vector3f* mReflectOffset_s{};
    // dynamic_param at offset 0x110
    bool* mIsCancelAttack_d{};
    // dynamic_param at offset 0x118
    sead::Vector3f* mTargetPos_d{};
    // Zeroed by the ctor together with the members above.
    ksys::Timer _120{};
    ksys::Timer _12c{};
    ksys::Timer _138{};
    u32 _144{};
    u8 _148{};
    bool _149{};
    bool _14a{};
    u32 _14c = 2;
    sead::Quatf _150;
    sead::Quatf _160;
    f32 _170 = 0;
    bool _174 = false;
    ksys::act::BoneHandle _178;
    ksys::act::BoneHandle _220;
    gsys::BoneAccessKeyEx _2c8;
    gsys::BoneAccessKeyEx _300;
};
KSYS_CHECK_SIZE_NX150(SiteBossShootNormalArrowRoot, 0x338);

}  // namespace uking::ai
