#pragma once

#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class Ragdoll : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Ragdoll, ksys::act::ai::Action)
public:
    explicit Ragdoll(const InitArg& arg);
    ~Ragdoll() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual bool m32();
    virtual void m33(const sead::Vector3f& velocity);
    virtual bool m34();
    virtual bool m35();
    virtual bool m36();
    virtual s32 m37() { return *mForceFinishTime_s; }
    virtual void m38();
    virtual void m39();
    virtual s32 m40();

    // 0x7100226488: the part of enter_ that sets up the animation state and the timers.
    void sub_7100226488();
    // 0x7100226a30: the end of the ragdoll motion: plays the stable AS and starts the final timer.
    void sub_7100226A30();
    // 0x7100227134: resets the controller and switches it to the hover motion type without gravity.
    void sub_7100227134();
    // 0x7100227184: drops the weapons (or the item) with the velocity of sub_7100227278 (inlined into m38).
    void sub_7100227184();
    // 0x7100227278: the velocity of the dropped weapons (horizontal speed away from the actor, vertical speed).
    void sub_7100227278(sead::Vector3f* out);
    // 0x7100226b04: moves the root bone offset towards the down-back / down-front controller offset.
    void sub_7100226B04();

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mInWaterDownTime_s{};
    // static_param at offset 0x30
    const int* mForceFinishTime_s{};
    // static_param at offset 0x38
    const int* mOnGroundDownTime_s{};
    // static_param at offset 0x40
    const int* mStartUpdateFriction_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x50
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x58
    const float* mGetUpGroundAngle_s{};
    // static_param at offset 0x60
    const float* mForceEndWaterDepth_s{};
    // static_param at offset 0x68
    const bool* mIsWaitAS_s{};
    // static_param at offset 0x70
    const bool* mIsItemDrop_s{};
    // static_param at offset 0x78
    const bool* mIsCheckVibrate_s{};
    // static_param at offset 0x80
    sead::SafeString mASName_s{};
    // static_param at offset 0x90
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0xa0
    sead::SafeString mStableASName_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mDownBackCtrlOffset_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mDownFrontCtrlOffset_s{};
    f32 _c0 = 0;
    f32 _c4 = 0;
    f32 _c8 = 0;
    s32 _cc = 0;
    s32 _d0 = 0;
    f32 _d4 = 0;
    s32 _d8 = 0;
    s32 _dc = 0;
    f32 _e0 = 0;
    s32 _e4 = 0;
    s32 _e8 = 0;
    s32 _ec = -1;
    f32 _f0 = 0;
    f32 _f4 = 1.0f;
    Unk_71000b0800<Unk_7102384718> _f8;
    ksys::act::CCAccessor mCCAccessor;
    void* _108 = nullptr;
    // aitree_variable at offset 0x110
    void* mCRBOffsetUnit_a{};
};

KSYS_CHECK_SIZE_NX150(Ragdoll, 0x118);

}  // namespace uking::action
