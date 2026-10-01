#include "Game/AI/Action/actionForkGravityScaleChange.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ForkGravityScaleChange::ForkGravityScaleChange(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGravityScaleChange::~ForkGravityScaleChange() = default;

bool ForkGravityScaleChange::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGravityScaleChange::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* cc = mActor->getCharacterController()) {
        _28 = cc->get110();
        cc->sub_7100F5EEB8(*mScale_s);
    } else if (auto* body = mActor->getMainBody()) {
        _28 = body->getGravityFactor();
        body->setGravityFactor(*mScale_s);
    }
    mFlags.set(Flag::Changeable);
}

void ForkGravityScaleChange::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(_28);
    else if (auto* body = mActor->getMainBody())
        body->setGravityFactor(_28);
}

void ForkGravityScaleChange::loadParams_() {
    getStaticParam(&mScale_s, "Scale");
}

void ForkGravityScaleChange::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
