#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class ZoraSurfing : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ZoraSurfing, ksys::act::ai::Action)
public:
    explicit ZoraSurfing(const InitArg& arg);
    ~ZoraSurfing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual bool m37();
    virtual void m38();
    virtual const sead::SafeString* m39();
    void sub_71002C2AD0();

    // FIXME: remove this
    /* 0x20 */ Unk_71024f15c0 _20;
    u8 pad_0x80[0x30];
    // static_param at offset 0xb0
    const float* mRotRadPerSec_s{};
    // static_param at offset 0xb8
    const float* mWallHitTime_s{};
    // static_param at offset 0xc0
    const float* mFinRadius_s{};
    // static_param at offset 0xc8
    const float* mFinHeight_s{};
    // static_param at offset 0xd0
    const float* mFinRotate_s{};
    // static_param at offset 0xd8
    const float* mInWaterDepth_s{};
    // static_param at offset 0xe0
    const float* mFloatDepth_s{};
    // static_param at offset 0xe8
    const float* mFloatRadius_s{};
    // static_param at offset 0xf0
    const float* mFloatCycleTime_s{};
    // static_param at offset 0xf8
    const float* mChangeDepthSpeed_s{};
    // static_param at offset 0x100
    const float* mOnRailDistance_s{};
    // static_param at offset 0x108
    const float* mFarDistance_s{};
    // static_param at offset 0x110
    const float* mSpeed_s{};
    // static_param at offset 0x118
    const bool* mIsClampRotVel_s{};
    // static_param at offset 0x120
    sead::SafeString mASName_s{};
    // static_param at offset 0x130
    sead::SafeString mASNameJump_s{};
    // static_param at offset 0x140
    const sead::Vector3f* mAddCalcStickX_s{};
    // dynamic_param at offset 0x148
    sead::SafeString mUniqueName_d{};
    /* 0x158 */ ksys::act::CCAccessor _158;
    // Not modelled yet (static string pointers and floats, see the W constructor at 0x71002c1354).
    u8 _160[0x1d5 - 0x160];
    u8 _1d5;
    u8 _1d6[2];
};

}  // namespace uking::action
