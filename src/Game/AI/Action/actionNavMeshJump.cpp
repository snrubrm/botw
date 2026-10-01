#include "Game/AI/Action/actionNavMeshJump.h"

namespace uking::action {

NavMeshJump::NavMeshJump(const InitArg& arg) : JumpTo(arg) {}

void NavMeshJump::m32() {
    playAS("JumpStart", false, 0, 0, -1.0f);
}

void NavMeshJump::m33() {
    playAS("Jumping", false, 0, 0, -1.0f);
}

void NavMeshJump::m34() {
    playAS("JumpEnd", false, 0, 0, -1.0f);
}

}  // namespace uking::action
