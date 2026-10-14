#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LeaderDistanceSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LeaderDistanceSelector, ksys::act::ai::Ai)
public:
    explicit LeaderDistanceSelector(const InitArg& arg);
    ~LeaderDistanceSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void changeToInside();
    // 0x710047f8ac: changeChild("外側") with the leader position as TargetPos.
    void changeToOutside();

protected:
    // static_param at offset 0x38
    const float* mBoundaryDistance_s{};
    // static_param at offset 0x40
    const float* mOverlapDistance_s{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mLeaderActor_d{};
    f32 _50{};
    f32 _54{};
};

}  // namespace uking::ai
