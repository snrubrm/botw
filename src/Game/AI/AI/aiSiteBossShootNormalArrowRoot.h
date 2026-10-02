#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

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
    // Slots 49..52 (and 53 in SiteBossReflectArrowRoot) are not declared yet (argument types unknown).

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
    // Zeroed by the ctor together with the members above; layout from 0x150 (incl. two BoneHandle
    // objects at 0x178/0x220 and two gsys::BoneAccessKeyEx at 0x2c8/0x300, size 0x338) not declared yet.
    f32 _120{};
    u8 _124[0x144 - 0x124]{};
    u32 _144{};
    u8 _148{};
    bool _149{};
    bool _14a{};
};

}  // namespace uking::ai
