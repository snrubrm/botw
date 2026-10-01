#pragma once

#include "Game/AI/Action/actionBackStepBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStep : public BackStepBase {
    SEAD_RTTI_OVERRIDE(BackStep, BackStepBase)
public:
    explicit BackStep(const InitArg& arg);

protected:
    void m34() override;
    void m35() override;
    void m36() override;
    void m37() override;
};

}  // namespace uking::action
