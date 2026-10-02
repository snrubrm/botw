#include "Game/AI/Action/actionExplodeReserved.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Resource/Actor/resResourcePhysics.h"

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
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        const int set_idx = actor->getPhysics()->sub_7100FBB668(*sub_71007A24E4());
        auto* set = actor->getPhysics()->getRigidBodySet(set_idx);
        const int body_idx = set->findBodyIndexByHavokName(body->getHkBodyName());
        auto& set_param =
            actor->getParam()->getRes().mPhysics->getParamSet().getRigidBodySet(set_idx);
        auto& param = set_param.rigid_bodies[body_idx];
        body->setContactLayerAndGroundHit(param.getContactLayer(), param.getGroundHit());
        body->setGravityFactor(1.0f);
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, false);
}

void ExplodeReserved::loadParams_() {
    StopASPlay::loadParams_();
}

void ExplodeReserved::calc_() {
    StopASPlay::calc_();
    mActor->m107();
}

}  // namespace uking::action
