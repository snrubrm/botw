#pragma once

#include "Game/AI/AI/aiRailMoveRemains.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DemoRailMoveRemains : public RailMoveRemains {
    SEAD_RTTI_OVERRIDE(DemoRailMoveRemains, RailMoveRemains)
public:
    explicit DemoRailMoveRemains(const InitArg& arg);
    ~DemoRailMoveRemains() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    f32 m41() override;
    f32 m42() override;

protected:
    // dynamic_param at offset 0x80
    float* mDynSpeedScale_d{};
    // dynamic_param at offset 0x88
    float* mDynInitPosByRailRatio_d{};
};
KSYS_CHECK_SIZE_NX150(DemoRailMoveRemains, 0x90);

}  // namespace uking::ai
