#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>
#include "KingSystem/System/Timer.h"

namespace uking::action {

class MoveBase : public ActionEx {
    SEAD_RTTI_OVERRIDE(MoveBase, ActionEx)
public:
    explicit MoveBase(const InitArg& arg);
    ~MoveBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mWallHitLimitTime_s{};
    // static_param at offset 0x30
    const int* mMoveAngCliffLimitTime_s{};
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mRotSpd_s{};
    // static_param at offset 0x48
    const float* mFinRadius_s{};
    // static_param at offset 0x50
    const float* mFinRotate_s{};
    // static_param at offset 0x58
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x60
    const float* mAccRatio_s{};
    // static_param at offset 0x68
    const float* mJumpUpSpeedReduceRatio_s{};
    // static_param at offset 0x70
    const bool* mFollowGround_s{};
    // static_param at offset 0x78
    const bool* mIgnoreLastCurve_s{};
    // static_param at offset 0x80
    const bool* mIgnoreDecelerationFrontCliff_s{};
    // static_param at offset 0x88
    const bool* mIgnoreMoveDirCoHit_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    f32 _98 = 0;
    ksys::Timer _9c{0, 0, 1.0f};
    // unknown object (0x24 bytes; same type as TurnBase::_6c, methods 0x7100741034...)
    u8 _a8[0xcc - 0xa8];
    sead::Vector3f _cc;
    f32 _d8 = 0;
};

KSYS_CHECK_SIZE_NX150(MoveBase, 0xe0);

}  // namespace uking::action
