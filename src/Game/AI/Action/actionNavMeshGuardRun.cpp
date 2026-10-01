#include "Game/AI/Action/actionNavMeshGuardRun.h"

namespace uking::action {

NavMeshGuardRun::NavMeshGuardRun(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGuardRun::~NavMeshGuardRun() = default;

void NavMeshGuardRun::m34() {
    playAS("GuardRun", true, 0, 0, -1.0f);
}

}  // namespace uking::action
