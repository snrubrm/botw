#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventDisappearRaceResult : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventDisappearRaceResult, ksys::act::ai::Action)
public:
    explicit EventDisappearRaceResult(const InitArg& arg);
    ~EventDisappearRaceResult() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

};

}  // namespace uking::action
