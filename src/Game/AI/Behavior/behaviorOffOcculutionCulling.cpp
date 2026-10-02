#include "Game/AI/Behavior/behaviorOffOcculutionCulling.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

OffOcculutionCulling::OffOcculutionCulling(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OffOcculutionCulling::~OffOcculutionCulling() = default;

bool OffOcculutionCulling::m6(sead::Heap* heap) {
    return true;
}

void OffOcculutionCulling::loadParams() {

}

void OffOcculutionCulling::m8() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags14.reset(0x2000000);
}

void OffOcculutionCulling::m7() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags14.reset(0x2000000);
}

void OffOcculutionCulling::m9() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags14.set(0x2000000);
}

}  // namespace uking::behavior
