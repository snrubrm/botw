#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GiantNavMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GiantNavMoveTarget, ksys::act::ai::Ai)
public:
    explicit GiantNavMoveTarget(const InitArg& arg);
    ~GiantNavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mRepathTime_s{};
    // static_param at offset 0x50
    const float* mTooFarDist_s{};
    // static_param at offset 0x58
    const float* mTargetVMax_s{};
    // static_param at offset 0x60
    const float* mTargetVMin_s{};
    // static_param at offset 0x68
    const float* mFrontAngle_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // Result of the unnamed enemy helper 0x71005e2bcc (init_); type unknown.
    void* _78{};
    ksys::Timer _80;
};

}  // namespace uking::ai
