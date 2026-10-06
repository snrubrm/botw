#include "Game/AI/Action/actionTurnToActorBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::action {

TurnToActorBase::TurnToActorBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TurnToActorBase::~TurnToActorBase() = default;

bool TurnToActorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TurnToActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    _1c = actor->get7d0() != nullptr;
    if (_1c) {
        if (auto* physics = actor->getPhysics())
            physics->sub_7100FBA0F4();
        actor->sub_71011DAC3C(ksys::phys::MotionType::Keyframed, true);
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10);
    }
    as_list->sub_710115CE44("Root");
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
