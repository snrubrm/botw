#include "Game/Actor/Behavior/behaviorNeckRotateToPlayer.h"
#include "Game/Actor/Player/actPlayerBase.h"

namespace uking::behavior {

NeckRotateToPlayer::NeckRotateToPlayer(const InitArg& arg) : NeckControl(arg) {}

NeckRotateToPlayer::~NeckRotateToPlayer() = default;

bool NeckRotateToPlayer::init_(sead::Heap* heap) {
    return NeckControl::init_(heap);
}

void NeckRotateToPlayer::calc() {
    NeckControl::calc();
}

void NeckRotateToPlayer::enter() {
    NeckControl::enter();
}

void NeckRotateToPlayer::leave() {
    NeckControl::leave();
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
