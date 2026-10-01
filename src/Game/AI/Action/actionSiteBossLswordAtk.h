#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class SiteBossLswordAtk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordAtk, ksys::act::ai::Action)
public:
    explicit SiteBossLswordAtk(const InitArg& arg);
    ~SiteBossLswordAtk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mAttackPower_s{};
    // static_param at offset 0x30
    const int* mAddAttackPower_s{};
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x50
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x58
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x60
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x68
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x70
    const float* mNearDist_s{};
    // static_param at offset 0x78
    const float* mNearMoveSpeed_s{};
    // static_param at offset 0x80
    const float* mFarDist_s{};
    // static_param at offset 0x88
    const float* mFarMoveSpeed_s{};
    // static_param at offset 0x90
    const bool* mIsIgnoreCancelAttack_s{};
    // static_param at offset 0x98
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _b0;
    // unknown 0x24-byte object (copied word by word)
    u8 _bc[0xe0 - 0xbc];
    bool _e0 = false;
};

KSYS_CHECK_SIZE_NX150(SiteBossLswordAtk, 0xe8);

}  // namespace uking::action
