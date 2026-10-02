#include "Game/AI/Action/actionForkOnEnterCharCtrlInvalid.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ForkOnEnterCharCtrlInvalid::ForkOnEnterCharCtrlInvalid(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOnEnterCharCtrlInvalid::~ForkOnEnterCharCtrlInvalid() = default;

bool ForkOnEnterCharCtrlInvalid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnEnterCharCtrlInvalid::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EC44();
    else if (auto* body = mActor->getMainBody())
        body->removeFromWorld();
    mFlags.set(Flag::Changeable);
}

void ForkOnEnterCharCtrlInvalid::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnEnterCharCtrlInvalid::loadParams_() {}

void ForkOnEnterCharCtrlInvalid::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
