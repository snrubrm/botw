#pragma once

#include "Game/AI/AI/aiRangeSelectTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeLineReachSelectTwoAction : public RangeSelectTwoAction {
    SEAD_RTTI_OVERRIDE(RangeLineReachSelectTwoAction, RangeSelectTwoAction)
public:
    explicit RangeLineReachSelectTwoAction(const InitArg& arg);
    ~RangeLineReachSelectTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m36() override;

protected:
};

}  // namespace uking::ai
