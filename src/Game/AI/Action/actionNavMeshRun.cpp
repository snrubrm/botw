#include "Game/AI/Action/actionNavMeshRun.h"

namespace uking::action {

NavMeshRun::NavMeshRun(const InitArg& arg) : NavMeshMoveBase(arg) {}

void NavMeshRun::m34() {
    playAS("Run", true, 0, 0, -1.0f);
}

}  // namespace uking::action
