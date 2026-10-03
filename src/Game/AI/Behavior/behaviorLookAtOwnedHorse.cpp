#include "Game/AI/Behavior/behaviorLookAtOwnedHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

LookAtOwnedHorse::LookAtOwnedHorse(const InitArg& arg) : InterestNeckControl(arg) {}

LookAtOwnedHorse::~LookAtOwnedHorse() = default;

bool LookAtOwnedHorse::m6(sead::Heap* heap) {
    if (!InterestNeckControl::m6(heap))
        return false;
    _60 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void LookAtOwnedHorse::m7() {
    InterestNeckControl::m7();
    auto* spine_controller = mActor->sub_71011D8A10();
    if (!spine_controller || spine_controller->sub_7100D88CE0())
        return;
    if (!_60)
        return;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_60->_f70, &accessor))
        return;
    const sead::Vector3f horse_pos = accessor.getActorMtx().getTranslation();
    if ((mActor->getMtx().getTranslation() - horse_pos).length() < *mDistance_s) {
        spine_controller->_8 = accessor.getPreviousPos2();
        spine_controller->_d4 |= 2;
    }
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
