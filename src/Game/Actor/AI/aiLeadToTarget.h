#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LeadToTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LeadToTarget, ksys::act::ai::Ai)
public:
    explicit LeadToTarget(const InitArg& arg);
    ~LeadToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710047FE18();
    // 0x7100480428 (placeholder name)
    void changeToWait();

protected:
    // static_param at offset 0x38
    const float* mSuccessRadius_s{};
    // static_param at offset 0x40
    const float* mWaitDistance_s{};
    // static_param at offset 0x48
    const float* mResumeLeadDistance_s{};
    // static_param at offset 0x50
    const float* mOkPathFailRange_s{};
    // static_param at offset 0x58
    const float* mWaitFramesAfterArrive_s{};
    // static_param at offset 0x60
    const bool* mDontWaitIfLeaderIsAhead_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    ksys::act::BaseProcLink* mLeaderActor_d{};
    ksys::Timer _78{0, 0};
    f32 _84 = -1.0f;
    f32 _88 = -1.0f;
    f32 _8c = -1.0f;
    f32 _90 = -1.0f;
    bool _94 = false;
};
KSYS_CHECK_SIZE_NX150(LeadToTarget, 0x98);

}  // namespace uking::ai
