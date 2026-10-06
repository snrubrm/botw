#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class PriestBossMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossMove, ksys::act::ai::Action)
public:
    explicit PriestBossMove(const InitArg& arg);
    ~PriestBossMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m32(sead::Vector3f* forward);
    virtual void m33();
    virtual void m34(ksys::phys::CharacterController* controller, const sead::Vector3f& dir);
    virtual s32 m35(f32 distance, const sead::Vector3f& dir, const sead::Vector3f& pos);
    virtual bool m36(const sead::Vector3f& dir);
    virtual bool m37();

protected:
    void calc_() override;

    // 0x71000679d0 (declared only): updates `speed` (the move speed) from the current `speed`, the remaining
    // distance and angle to the target.
    void sub_71000679D0(f32* speed, f32 cur, f32 threshold, f32 dist, f32 angle, bool a, bool b);

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mWallHitLimitTime_s{};
    // static_param at offset 0x30
    const int* mMoveAngCliffLimitTime_s{};
    // static_param at offset 0x38
    const int* mNotMoveLimitTime_s{};
    // static_param at offset 0x40
    const float* mSpeed_s{};
    // static_param at offset 0x48
    const float* mAccRatio_s{};
    // static_param at offset 0x50
    const float* mInitRotSpd_s{};
    // static_param at offset 0x58
    const float* mAccRotSpd_s{};
    // static_param at offset 0x60
    const float* mMaxRotSpd_s{};
    // static_param at offset 0x68
    const float* mFinRadius_s{};
    // static_param at offset 0x70
    const float* mFinRotate_s{};
    // static_param at offset 0x78
    const float* mFrontCliffDistance_s{};
    // static_param at offset 0x80
    const float* mFrontCliffAngle_s{};
    // static_param at offset 0x88
    const float* mJumpUpSpeedReduceRatio_s{};
    // static_param at offset 0x90
    const float* mNotMoveDistanceThreshold_s{};
    // static_param at offset 0x98
    const bool* mFollowGround_s{};
    // static_param at offset 0xa0
    const bool* mIgnoreLastCurve_s{};
    // static_param at offset 0xa8
    const bool* mIgnoreDecelerationFrontCliff_s{};
    // static_param at offset 0xb0
    const bool* mIgnoreMoveDirCoHit_s{};
    // static_param at offset 0xb8
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xc8
    sead::Vector3f* mMoveTargetPos_d{};
    f32 _d0 = 0.0f;
    f32 _d4 = 0.0f;
    ksys::Timer _d8{0.0f, 0.0f, 1.0f};
    ksys::Timer _e4{0.0f, 0.0f, 1.0f};
    sead::Matrix33f _f0;
    sead::Vector3f _114;
    sead::Vector3f _120;
    f32 _12c = 0.0f;
    bool _130 = false;
    bool _131 = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossMove, 0x138);

}  // namespace uking::action
