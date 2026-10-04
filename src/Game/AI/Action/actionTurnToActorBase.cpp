#include "Game/AI/Action/actionTurnToActorBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

TurnToActorBase::TurnToActorBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TurnToActorBase::~TurnToActorBase() = default;

bool TurnToActorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TurnToActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TurnToActorBase::leave_() {
    auto* actor = mActor;
    if (auto* as_list = actor->getASList())
        as_list->sub_710115D0AC();
    if (_1c) {
        if (auto* physics = actor->getPhysics())
            physics->sub_7100FBA174();
        if (auto* controller = actor->getCharacterController())
            controller->sub_7100F60604();
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10);
    }
}

void TurnToActorBase::loadParams_() {}

void TurnToActorBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
