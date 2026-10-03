#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MoveLOSFeedback : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveLOSFeedback, ksys::act::ai::Ai)
public:
    explicit MoveLOSFeedback(const InitArg& arg);
    ~MoveLOSFeedback() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x71004b0f44 (placeholder name)
    void changeToCollide(const sead::Vector3f& hit_pos);

protected:
    // static_param at offset 0x38
    const float* mFramesCooldownFeedback_s{};
    // static_param at offset 0x40
    const float* mLOSCheckLength_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _50;
};

}  // namespace uking::ai
