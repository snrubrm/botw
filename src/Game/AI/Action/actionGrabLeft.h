#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabLeft : public Grab {
    SEAD_RTTI_OVERRIDE(GrabLeft, Grab)
public:
    explicit GrabLeft(const InitArg& arg);

protected:
    void m32() override;
};

}  // namespace uking::action
