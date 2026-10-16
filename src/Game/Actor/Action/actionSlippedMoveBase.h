#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadVector.h>

namespace uking::action {

class SlippedMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SlippedMoveBase, ksys::act::ai::Action)
public:
    explicit SlippedMoveBase(const InitArg& arg);
    ~SlippedMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100271294 (placeholder name): updates the wall-hit timer from a probe along `probe_dir`; false once it
    // exceeds WallHitLimitTime (or 10 while the probe hits).
    bool sub_7100271294(const sead::Vector3f& probe_dir, const sead::Vector3f& dir, bool* hit_out);

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mWallHitLimitTime_s{};
    // static_param at offset 0x30
    const float* mSpeed_s{};
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mFinRadius_s{};
    // static_param at offset 0x48
    const float* mFinRotate_s{};
    // static_param at offset 0x50
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x58
    const float* mAccRatio_s{};
    // static_param at offset 0x60
    const bool* mFollowGround_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // Wall-hit timer (runs while the actor is pushed against a wall; reset to rate 1 in enter_).
    ksys::Timer mWallHitTimer;
    sead::Matrix33f _7c;
    f32 _a0 = 0;
};

KSYS_CHECK_SIZE_NX150(SlippedMoveBase, 0xa8);

}  // namespace uking::action
