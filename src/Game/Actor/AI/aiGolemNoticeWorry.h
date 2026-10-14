#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemNoticeWorry : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemNoticeWorry, ksys::act::ai::Ai)
public:
    explicit GolemNoticeWorry(const InitArg& arg);
    ~GolemNoticeWorry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Inline-only in the original (name guess; evidence: calc_'s isCurrentChild temporaries share the param pack's slot).
    void changeToLookAround();

    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
