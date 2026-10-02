#include "Game/AI/Behavior/behaviorNeckRotateToPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::behavior {

NeckRotateToPlayer::NeckRotateToPlayer(const InitArg& arg) : NeckControl(arg) {}

NeckRotateToPlayer::~NeckRotateToPlayer() = default;

bool NeckRotateToPlayer::m6(sead::Heap* heap) {
    return NeckControl::m6(heap);
}

void NeckRotateToPlayer::m7() {
    NeckControl::m7();
}

void NeckRotateToPlayer::m8() {
    NeckControl::m8();
}

void NeckRotateToPlayer::m9() {
    NeckControl::m9();
}

void NeckRotateToPlayer::loadParams() {
    NeckControl::loadParams();
}

void NeckRotateToPlayer::m15(sead::Vector3f* out) {
    ksys::act::acc::PlayerBase accessor;
    accessor.getPlayerFromPlayerInfo();
    out->set(accessor.getPreviousPos());
}

}  // namespace uking::behavior
