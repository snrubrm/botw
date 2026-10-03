#include "Game/AI/Action/actionGoronHeroDescendentAppear.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GoronHeroDescendentAppear::GoronHeroDescendentAppear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GoronHeroDescendentAppear::~GoronHeroDescendentAppear() = default;

bool GoronHeroDescendentAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GoronHeroDescendentAppear::loadParams_() {}

bool GoronHeroDescendentAppear::oneShot_() {
    if (auto* cc = mActor->getCharacterController()) {
        cc->sub_7100F62BC0(false);
        cc->sub_7100F60604();
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    return true;
}

}  // namespace uking::action
