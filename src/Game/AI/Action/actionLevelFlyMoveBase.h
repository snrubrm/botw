#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71006F3CC4.h"
#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class LevelFlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LevelFlyMoveBase, ksys::act::ai::Action)
public:
    explicit LevelFlyMoveBase(const InitArg& arg);
    ~LevelFlyMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual bool m33();
    // Writes the target position (raised by TargetHeightOffset) to `pos`.
    virtual void m34(sead::Vector3f* pos);
    // 0x71001dacb4 (not decompiled yet).
    virtual void m35(sead::Vector3f* dir, f32 speed);
    // Inline (emitted out of line in another TU, 0x71001ba780 / 0x71001ba784).
    virtual void m36(sead::Vector3f* dir) {}
    virtual void m37(sead::Vector3f* dir) {}

    // static_param at offset 0x20
    const float* mXZSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mFinRotate_s{};
    // static_param at offset 0x38
    const float* mHorizontalFinRadius_s{};
    // static_param at offset 0x40
    const float* mVerticalFinLength_s{};
    // static_param at offset 0x48
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x50
    const float* mRotRatio_s{};
    // static_param at offset 0x58
    const float* mRiseSpeed_s{};
    // static_param at offset 0x60
    const float* mDownSpeed_s{};
    // static_param at offset 0x68
    const float* mCheckStopSpeed_s{};
    // static_param at offset 0x70
    const float* mVibrateMemoryStep_s{};
    // static_param at offset 0x78
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0x80
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0x88
    const bool* mIsOverRise_s{};
    // static_param at offset 0x90
    const bool* mIsSlowDownNearGoal_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0xa0
    void* mRefPosVibrateChecker_a{};
    /* 0xa8 */ ksys::VFRValue _a8;
    /* 0xb4 */ ksys::VFRValue _b4;
    /* 0xc0 */ sead::Vector3f _c0{0, 0, 0};
    /* 0xcc */ sead::Vector3f _cc{0, 0, 0};
    /* 0xd8 */ sead::Matrix33f _d8;
    /* 0xfc */ ksys::VFRValue _fc;
    /* 0x108 */ Unk_71000b0800<Unk_71025b0578> _108;
    /* 0x110 */ ksys::act::CCAccessor _110;
    /* 0x118 */ Unk_7102450038 _118{this};
};
KSYS_CHECK_SIZE_NX150(LevelFlyMoveBase, 0x138);

}  // namespace uking::action
