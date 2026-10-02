#include "Game/AI/AI/aiMagneStickRoot.h"
#include "Game/gameGearMgr.h"
#include <algorithm>
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
    if (auto* gear_mgr = GearMgr::instance())
        gear_mgr->sub_71006694B4(mActor);
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

void MagneStickRoot::m35() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006694B4(mActor);
}

void MagneStickRoot::m34() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006692F0(mActor, *mJoinSystemGroup_m);
}

void MagneStickRoot::m36() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_710066956C(mActor, *mJoinSystemGroup_m);
}

void MagneStickRoot::m37() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006695DC(mActor);
}

void MagneStickRoot::m38() {
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr || !mActor || !*mJoinSystemGroup_m)
        return;
    auto* handler = gear_mgr->_1050;
    if (auto* body = mActor->getMainBody())
        body->setSystemGroupHandler(handler);
}

void MagneStickRoot::m39() {
    if (!GearMgr::instance() || !mActor || !*mJoinSystemGroup_m)
        return;
    if (auto* body = mActor->getMainBody())
        body->setSystemGroupHandler(nullptr);
}

void MagneStickRoot::m49(sead::Vector3f* out, sead::Vector3f pos, const sead::Vector3f& target) {
    auto* actor = mActor;
    if (!actor)
        return;
    const sead::Vector3f diff = pos - target;
    const f32 scale = 1.0f / std::max(diff.length(), 0.5f) * 0.25f;
    *out = actor->getMtx().getTranslation() + diff * scale;
}

}  // namespace uking::ai
