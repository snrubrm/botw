#include "Game/AI/Behavior/behaviorNavMeshNonAvoidPlayer.h"

namespace uking::behavior {

NavMeshNonAvoidPlayer::NavMeshNonAvoidPlayer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NavMeshNonAvoidPlayer::~NavMeshNonAvoidPlayer() = default;

bool NavMeshNonAvoidPlayer::m6(sead::Heap* heap) {
    return true;
}

void NavMeshNonAvoidPlayer::m7() {}

void NavMeshNonAvoidPlayer::loadParams() {

}

}  // namespace uking::behavior
