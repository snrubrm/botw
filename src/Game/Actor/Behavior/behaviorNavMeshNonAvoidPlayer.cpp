#include "Game/Actor/Behavior/behaviorNavMeshNonAvoidPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::behavior {

NavMeshNonAvoidPlayer::NavMeshNonAvoidPlayer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NavMeshNonAvoidPlayer::~NavMeshNonAvoidPlayer() = default;

bool NavMeshNonAvoidPlayer::init_(sead::Heap* heap) {
    return true;
}

void NavMeshNonAvoidPlayer::calc() {}

void NavMeshNonAvoidPlayer::enter() {
    if (auto* nav = mActor->m45()) {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (auto* other = accessor.sub_7100D0F57C())
            _28 = nav->sub_7100F7D1CC(other);
    }
}

void NavMeshNonAvoidPlayer::leave() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F7D308(_28);
}

void NavMeshNonAvoidPlayer::loadParams() {

}

}  // namespace uking::behavior
