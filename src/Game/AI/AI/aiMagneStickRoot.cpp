#include "Game/AI/AI/aiMagneStickRoot.h"
#include <math/seadBoundBox.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

MagneStickRoot::MagneStickRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneStickRoot::~MagneStickRoot() = default;

bool MagneStickRoot::init_(sead::Heap* heap) {
    if (*mRegistFromBeginning_m)
        m34();
    _8c = ksys::Timer(1, 1);
    return true;
}

void MagneStickRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _7c = 0;
    changeChild("通常");
    _8c = ksys::Timer(1, 1);
    auto* actor = mActor;
    if (!actor)
        return;

    auto* body = actor->getMainBody();
    if (!body)
        return;

    _98 = actor->findPhysicsBodyByName("EntitySensor", "SensorBody");
    sead::BoundBox3f aabb;
    body->getAabbInLocal(&aabb);
    _88 = aabb.getMax().z - aabb.getMin().z;
    _80 = body->getMaxLinearVelocity();
    _84 = body->getMaxAngularVelocity();
    sub_71007A458C(actor, *mIgnoreObstacle_m);
}

void MagneStickRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneStickRoot::loadParams_() {
    getStaticParam(&mDefaultConnectionDistance_s, "DefaultConnectionDistance");
    getStaticParam(&mCollideRadiusFactor_s, "CollideRadiusFactor");
    getMapUnitParam(&mCollideRadius_m, "CollideRadius");
    getMapUnitParam(&mJoinSystemGroup_m, "JoinSystemGroup");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getMapUnitParam(&mIgnoreObstacle_m, "IgnoreObstacle");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

}  // namespace uking::ai
