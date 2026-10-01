#include "Game/AI/Action/actionNavMeshWalk.h"

namespace uking::action {

NavMeshWalk::NavMeshWalk(const InitArg& arg) : NavMeshAction(arg) {}

void NavMeshWalk::m34() {
    playAS("Walk", true, 0, 0, -1.0f);
}

}  // namespace uking::action
