#include "Game/AI/Action/actionExplodeReserved.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ExplodeReserved::ExplodeReserved(const InitArg& arg) : StopASPlay(arg) {}

ExplodeReserved::~ExplodeReserved() = default;

bool ExplodeReserved::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void ExplodeReserved::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
    if (auto* body = mActor->getMainBody()) {
        body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        body->setGravityFactor(0.0f);
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, true);
}

void ExplodeReserved::leave_() {
    StopASPlay::leave_();
}

void ExplodeReserved::loadParams_() {
    StopASPlay::loadParams_();
}

void ExplodeReserved::calc_() {
    StopASPlay::calc_();
}

}  // namespace uking::action
