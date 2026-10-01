#include "Game/AI/Action/actionNavMeshGuardWalk.h"

namespace uking::action {

NavMeshGuardWalk::NavMeshGuardWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshGuardWalk::~NavMeshGuardWalk() = default;

void NavMeshGuardWalk::m34() {
    playAS("GuardWalk", true, 0, 0, -1.0f);
}

}  // namespace uking::action
