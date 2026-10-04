#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "Game/AI/aiRandomTimer.h"
#include "KingSystem/System/Timer.h"

// 0x7100729d18 (placeholder name; declared only): writes the next swarm velocity to `out` (from the current one
// `dir` and the speed), sets `*flag` when a new target was picked; returns false when the swarm stopped.
bool sub_7100729D18(ksys::act::Actor* actor, sead::Vector3f* out, const sead::Vector3f& dir, f32 speed,
                    s32* flag, bool a6);

namespace uking::ai {

class AddSwarmMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddSwarmMove, ksys::act::ai::Ai)
public:
    explicit AddSwarmMove(const InitArg& arg);
    ~AddSwarmMove() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIgnoreSensorTime_s{};
    // static_param at offset 0x40
    const float* mSubSpeed_s{};
    // static_param at offset 0x48
    const float* mSubAccRateMin_s{};
    // static_param at offset 0x50
    const float* mSubAccRateMax_s{};
    // static_param at offset 0x58
    const bool* mIsEndBySensor_s{};
    // static_param at offset 0x60
    sead::SafeString mAnimName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    bool _78 = false;
    ksys::Timer _7c{0, 0, 0};
    sead::Vector3f _88{0, 0, 0};
    RandomTimer _94;
};

}  // namespace uking::ai
