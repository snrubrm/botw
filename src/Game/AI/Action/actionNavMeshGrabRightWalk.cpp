#include "Game/AI/Action/actionNavMeshGrabRightWalk.h"

namespace uking::action {

NavMeshGrabRightWalk::NavMeshGrabRightWalk(const InitArg& arg) : NavMeshAction(arg) {}

void NavMeshGrabRightWalk::m34() {
    playAS("GrabRightWalk", false, 0, 0, -1.0f);
}

}  // namespace uking::action
