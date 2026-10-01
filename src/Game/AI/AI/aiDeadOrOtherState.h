#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DeadOrOtherState : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DeadOrOtherState, ksys::act::ai::Ai)
public:
    explicit DeadOrOtherState(const InitArg& arg);
    void calc_() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
