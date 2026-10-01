#include "Game/AI/Action/actionKeepStandingPosture.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

KeepStandingPosture::KeepStandingPosture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KeepStandingPosture::~KeepStandingPosture() = default;

bool KeepStandingPosture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KeepStandingPosture::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_3a, true);
}

void KeepStandingPosture::leave_() {
    ksys::act::ai::Action::leave_();
}

void KeepStandingPosture::loadParams_() {}

void KeepStandingPosture::calc_() {
    auto* body = mActor->getMainBody();
    sead::Matrix34f mtx;
    body->getTransform(&mtx);
    mtx.m[1][2] = 0.0f;
    mtx.m[2][1] = 0.0f;
    mtx.m[1][0] = 0.0f;
    mtx.m[0][1] = 0.0f;
    mtx.m[1][1] = 1.0f;
    sead::Vector3f angular_velocity;
    body->computeAngularVelocity(&angular_velocity, mtx);
    body->setAngularVelocity(angular_velocity);
}

}  // namespace uking::action
