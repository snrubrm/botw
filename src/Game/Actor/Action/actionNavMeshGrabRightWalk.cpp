#include "Game/Actor/Action/actionNavMeshGrabRightWalk.h"

namespace uking::action {

NavMeshGrabRightWalk::NavMeshGrabRightWalk(const InitArg& arg) : NavMeshMoveBase(arg) {}

void NavMeshGrabRightWalk::m34() {
    playAS("GrabRightWalk", false, 0, 0, -1.0f);
}

}  // namespace uking::action
