#pragma once

#include "Game/AI/AI/aiLynelNavMoveNoStop.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelNavMoveTarget : public LynelNavMoveNoStop {
    SEAD_RTTI_OVERRIDE(LynelNavMoveTarget, LynelNavMoveNoStop)
public:
    explicit LynelNavMoveTarget(const InitArg& arg);
    ~LynelNavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;
    bool m35() override;

    // 0x7100493790 (placeholder name; declared only)
    bool sub_7100493790(bool a1);

protected:
    // static_param at offset 0x70
    const int* mStopGear_s{};
    // static_param at offset 0x78
    const float* mCliffCheckDist_s{};
};

}  // namespace uking::ai
