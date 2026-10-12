#pragma once

#include "Game/AI/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshEscape : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshEscape, NavMeshMoveBase)
public:
    explicit NavMeshEscape(const InitArg& arg);

protected:
    void m34() override;
};

}  // namespace uking::action
