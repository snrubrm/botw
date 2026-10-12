#pragma once

#include "Game/AI/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardWalk : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGuardWalk, NavMeshMoveBase)
public:
    explicit NavMeshGuardWalk(const InitArg& arg);
    ~NavMeshGuardWalk() override;

protected:
    void m34() override;
};

}  // namespace uking::action
