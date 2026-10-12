#pragma once

#include "Game/AI/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStop : public StopBase {
    SEAD_RTTI_OVERRIDE(ForkStop, StopBase)
public:
    explicit ForkStop(const InitArg& arg);
    ~ForkStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
