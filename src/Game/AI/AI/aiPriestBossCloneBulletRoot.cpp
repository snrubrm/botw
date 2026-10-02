#include "Game/AI/AI/aiPriestBossCloneBulletRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"

namespace uking::ai {

PriestBossCloneBulletRoot::PriestBossCloneBulletRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossCloneBulletRoot::~PriestBossCloneBulletRoot() = default;

bool PriestBossCloneBulletRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

// NON_MATCHING: the original computes the ground hit mask before calling getContactLayer()
void PriestBossCloneBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    sub_71007A3800(mActor);
    changeChild("待機");
    _48 = ksys::Timer(360.0f, 360.0f);
    _68.x();
    _118 = false;

    if (auto* body = mActor->getMainBody()) {
        body->setGroundHitMask(body->getContactLayer(),
                               ksys::phys::orEntityGroundHitMask(0, ksys::phys::GroundHit::Giant));
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
    if (auto* body = mActor->getPhysicsMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void PriestBossCloneBulletRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossCloneBulletRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossCloneBulletRoot::handleMessage_(const ksys::Message& message) {
    return !_68.m2(message);
}

}  // namespace uking::ai
