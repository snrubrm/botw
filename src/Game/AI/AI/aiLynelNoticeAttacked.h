#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LynelNoticeAttacked : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelNoticeAttacked, ksys::act::ai::Ai)
public:
    explicit LynelNoticeAttacked(const InitArg& arg);
    ~LynelNoticeAttacked() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRepeatMax_s{};
    // static_param at offset 0x40
    const int* mRepeatResetTime_s{};
    // static_param at offset 0x48
    const float* mForceReturnDistFromHomePos_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x58
    int* mLynelNoticeAttackRepeatNum_a{};
    sead::Vector3f _60{0, 0, 0};
    ksys::Timer _6c;
};

}  // namespace uking::ai
