#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Utils/Unk_7100e726a8.h"
#include "KingSystem/Utils/Unk_7100e7277c.h"

namespace uking::action {

class NpcSwimMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NpcSwimMove, ksys::act::ai::Action)
public:
    explicit NpcSwimMove(const InitArg& arg);
    ~NpcSwimMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    // inline in the original (emitted out of line in this TU); signature is a guess
    virtual const sead::SafeString& m33() { return mASName_s; }

    // static_param at offset 0x20
    const float* mRotRadPerSec_s{};
    // static_param at offset 0x28
    const float* mWallHitTime_s{};
    // static_param at offset 0x30
    const float* mFinRadius_s{};
    // static_param at offset 0x38
    const float* mFinHeight_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mInWaterDepth_s{};
    // static_param at offset 0x50
    const float* mFloatDepth_s{};
    // static_param at offset 0x58
    const float* mFloatRadius_s{};
    // static_param at offset 0x60
    const float* mFloatCycleTime_s{};
    // static_param at offset 0x68
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x70
    const bool* mIsClampRotVel_s{};
    // static_param at offset 0x78
    sead::SafeString mASName_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mAddCalcStickX_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    ksys::act::CCAccessor _98;
    Unk_7100e726a8 _a0;
    Unk_7100e7277c _e0;
    sead::Vector3f _f0;
    u8 _fc[0xc];
    f32 _108;
    f32 _10c;
    f32 _110;
    bool _114;

    // 0x71002001a4 (placeholder name): sets _110 to the vertical speed that keeps the actor floating.
    void sub_71002001A4();
};

KSYS_CHECK_SIZE_NX150(NpcSwimMove, 0x118);

}  // namespace uking::action
