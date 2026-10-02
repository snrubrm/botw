#include "Game/AI/Behavior/behaviorSetForceSmallRagdoll.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

SetForceSmallRagdoll::SetForceSmallRagdoll(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetForceSmallRagdoll::~SetForceSmallRagdoll() = default;

bool SetForceSmallRagdoll::m6(sead::Heap* heap) {
    return true;
}

void SetForceSmallRagdoll::m7() {}

void SetForceSmallRagdoll::loadParams() {

}

void SetForceSmallRagdoll::m8() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e82 |= 0x200;
}

void SetForceSmallRagdoll::m9() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e82 &= ~0x200;
}

}  // namespace uking::behavior
