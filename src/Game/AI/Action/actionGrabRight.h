#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabRight : public Grab {
    SEAD_RTTI_OVERRIDE(GrabRight, Grab)
public:
    explicit GrabRight(const InitArg& arg);

protected:
    void m32() override;
};

}  // namespace uking::action
