#include "Game/AI/Behavior/behaviorLookAtOwnedHorse.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

LookAtOwnedHorse::LookAtOwnedHorse(const InitArg& arg) : InterestNeckControl(arg) {}

LookAtOwnedHorse::~LookAtOwnedHorse() = default;

bool LookAtOwnedHorse::m6(sead::Heap* heap) {
    if (!InterestNeckControl::m6(heap))
        return false;
    _60 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void LookAtOwnedHorse::m8() {
    InterestNeckControl::m8();
}

void LookAtOwnedHorse::m9() {
    InterestNeckControl::m9();
}

void LookAtOwnedHorse::loadParams() {
    InterestNeckControl::loadParams();
    getStaticParam(&mDistance_s, "Distance");
}

}  // namespace uking::behavior
