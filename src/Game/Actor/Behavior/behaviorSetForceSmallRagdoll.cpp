#include "Game/Actor/Behavior/behaviorSetForceSmallRagdoll.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

SetForceSmallRagdoll::SetForceSmallRagdoll(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetForceSmallRagdoll::~SetForceSmallRagdoll() = default;

bool SetForceSmallRagdoll::init_(sead::Heap* heap) {
    return true;
}

void SetForceSmallRagdoll::calc() {}

void SetForceSmallRagdoll::loadParams() {

}

void SetForceSmallRagdoll::enter() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e82 |= 0x200;
}

void SetForceSmallRagdoll::leave() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e82 &= ~0x200;
}

}  // namespace uking::behavior
