#include "Game/AI/Action/actionNavMeshGrabLeftWalk.h"

namespace uking::action {

NavMeshGrabLeftWalk::NavMeshGrabLeftWalk(const InitArg& arg) : NavMeshAction(arg) {}

void NavMeshGrabLeftWalk::m34() {
    playAS("GrabLeftWalk", false, 0, 0, -1.0f);
}

}  // namespace uking::action
