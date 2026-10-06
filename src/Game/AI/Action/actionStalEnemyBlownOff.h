#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StalEnemyBlownOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StalEnemyBlownOff, ksys::act::ai::Action)
public:
    explicit StalEnemyBlownOff(const InitArg& arg);
    ~StalEnemyBlownOff() override;
    bool handleMessage_(const ksys::Message* message) override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override { return _154 > 1; }

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDownTimeBase_s{};
    // static_param at offset 0x28
    const int* mDownTimeRand_s{};
    // static_param at offset 0x30
    const float* mRecoverTimer_s{};
    // static_param at offset 0x38
    const float* mHeadShotSpeed_s{};
    // static_param at offset 0x40
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x50
    const float* mHeadSpeedRate_s{};
    // static_param at offset 0x58
    const float* mMinHeadSpeedY_s{};
    // static_param at offset 0x60
    const float* mMinHeadSpeedXZ_s{};
    // static_param at offset 0x68
    const bool* mHeadShotUseAddVec_s{};
    // static_param at offset 0x70
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0x80
    sead::SafeString mDisableBoneName_s{};
    // static_param at offset 0x90
    sead::SafeString mEnableConstraintName_s{};
    // static_param at offset 0xa0
    sead::SafeString mUseRagConName_s{};
    // static_param at offset 0xb0
    sead::SafeString mBlownOffASName_s{};
    // static_param at offset 0xc0
    sead::SafeString mPreUniteASName_s{};
    // static_param at offset 0xd0
    sead::SafeString mUniteASName_s{};
    // static_param at offset 0xe0
    sead::SafeString mDieASName_s{};
    // static_param at offset 0xf0
    sead::SafeString mHeadRagdollRigidNames_s{};
    // static_param at offset 0x100
    sead::SafeString mArmRagdollRigidNames_s{};
    // static_param at offset 0x110
    const sead::Vector3f* mDownBackCtrlOffset_s{};
    // static_param at offset 0x118
    const sead::Vector3f* mDownFrontCtrlOffset_s{};
    // static_param at offset 0x120
    const sead::Vector3f* mHeadShotAddVec_s{};
    // static_param at offset 0x128
    const sead::Vector3f* mHeadRotateOffset_s{};
    // Not decompiled yet (see the ctor at 0x71002734c8): 0x130-0x154 are zeroed together with the static params.
    u8 _130[0x154 - 0x130];
    s32 _154 = -1;
    u8 _158[0x160 - 0x158];
    s32 _160 = -1;
    f32 _164 = 0.0f;
    u8 _168[0x16d - 0x168];
    bool _16d = false;
    bool _16e = false;

    // 0x71002749b4 (placeholder name): raises the character controller's `_110` by the frame time.
    void sub_71002749B4();
    // 0x7100274d98 (placeholder name): tilts the character controller to the ragdoll's pose.
    void sub_7100274D98();
    // 0x710027588c (placeholder name): the velocity of a dropped weapon (the actor's horizontal velocity scaled to
    // WeaponDropSpeedXZ, WeaponDropSpeedY upwards).
    void sub_710027588C(sead::Vector3f* velocity);
};

}  // namespace uking::action
