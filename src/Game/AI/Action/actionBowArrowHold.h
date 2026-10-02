#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowArrowHold : public BindAction {
    SEAD_RTTI_OVERRIDE(BowArrowHold, BindAction)
public:
    explicit BowArrowHold(const InitArg& arg);

protected:
    void m32() override;
    ksys::act::Actor* m33() override;
};

}  // namespace uking::action
