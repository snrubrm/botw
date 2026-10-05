#include "Game/AI/Behavior/behaviorNavMeshNonAvoidPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::behavior {

NavMeshNonAvoidPlayer::NavMeshNonAvoidPlayer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NavMeshNonAvoidPlayer::~NavMeshNonAvoidPlayer() = default;

bool NavMeshNonAvoidPlayer::m6(sead::Heap* heap) {
    return true;
}

void NavMeshNonAvoidPlayer::m7() {}

void NavMeshNonAvoidPlayer::m8() {
    if (auto* nav = mActor->m45()) {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (auto* other = accessor.sub_7100D0F57C())
            _28 = nav->sub_7100F7D1CC(other);
    }
}

void NavMeshNonAvoidPlayer::m9() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F7D308(_28);
}

void NavMeshNonAvoidPlayer::loadParams() {

}

}  // namespace uking::behavior
