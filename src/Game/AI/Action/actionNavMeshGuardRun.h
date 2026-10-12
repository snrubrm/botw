#pragma once

#include "Game/AI/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardRun : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGuardRun, NavMeshMoveBase)
public:
    explicit NavMeshGuardRun(const InitArg& arg);
    ~NavMeshGuardRun() override;

protected:
    void m34() override;
};

}  // namespace uking::action
