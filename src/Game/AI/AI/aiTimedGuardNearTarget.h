#pragma once

#include "Game/AI/AI/aiGuardNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimedGuardNearTarget : public GuardNearTarget {
    SEAD_RTTI_OVERRIDE(TimedGuardNearTarget, GuardNearTarget)
public:
    explicit TimedGuardNearTarget(const InitArg& arg);
    ~TimedGuardNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35(float distance) override;
    bool m36(float distance) override;
    bool m38() override { return true; }
    virtual bool m39(float distance);

protected:
    // static_param at offset 0x88
    const int* mGuardEndTime_s{};
    // static_param at offset 0x90
    const float* mGuardStartAngle_s{};
    // static_param at offset 0x98
    const float* mGuardEndAngle_s{};
    float _a0 = 0;
    int _a4 = 0;
    int _a8 = 0;
};

}  // namespace uking::ai
