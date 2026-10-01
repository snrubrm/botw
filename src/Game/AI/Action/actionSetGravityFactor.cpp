#include "Game/AI/Action/actionSetGravityFactor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetGravityFactor::SetGravityFactor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetGravityFactor::~SetGravityFactor() = default;

bool SetGravityFactor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetGravityFactor::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(*mValue_s);
    mFlags.set(Flag::Changeable);
}

void SetGravityFactor::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetGravityFactor::loadParams_() {
    getStaticParam(&mValue_s, "Value");
}

void SetGravityFactor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
