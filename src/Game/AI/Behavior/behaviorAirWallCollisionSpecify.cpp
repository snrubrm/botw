#include "Game/AI/Behavior/behaviorAirWallCollisionSpecify.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"

namespace uking::behavior {

AirWallCollisionSpecify::AirWallCollisionSpecify(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void AirWallCollisionSpecify::m7() {
    if (_48 == *mAirWallCollision_m)
        return;
    bool set = true;
    switch (*mAirWallCollision_m) {
    case 1:
        _28.setFunction(&AirWallCollisionSpecify::sub_71006163B4);
        break;
    case 2:
        _28.setFunction(&AirWallCollisionSpecify::sub_7100616700);
        break;
    default:
        set = false;
        break;
    }
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor)) {
        wall->sub_7100E245B8(set ? &_28 : nullptr);
        _48 = *mAirWallCollision_m;
    }
}

void AirWallCollisionSpecify::m8() {
    _48 = 3;
    if (_48 == *mAirWallCollision_m)
        return;
    bool set = true;
    switch (*mAirWallCollision_m) {
    case 1:
        _28.setFunction(&AirWallCollisionSpecify::sub_71006163B4);
        break;
    case 2:
        _28.setFunction(&AirWallCollisionSpecify::sub_7100616700);
        break;
    default:
        set = false;
        break;
    }
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor)) {
        wall->sub_7100E245B8(set ? &_28 : nullptr);
        _48 = *mAirWallCollision_m;
    }
}

void AirWallCollisionSpecify::loadParams() {
    getMapUnitParam(&mAirWallCollision_m, "AirWallCollision");
}

void AirWallCollisionSpecify::sub_71006163B4(ksys::phys::RigidBody* body) {
    using ksys::phys::ContactLayer;
    using ksys::phys::GroundHit;
    u32 mask = 0;
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::NPC);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Animal);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Camera);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::AttackHitPlayer);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::AttackHitEnemy);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Arrow);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Bomb);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Magnet);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::CameraBody);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::IK);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Grudge);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::MovingTrolley);
    mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::LineOfSight);
    body->setGroundHitMask(body->getContactLayer(), mask);
    body->enableContactLayer(ContactLayer::EntityObject);
    body->enableContactLayer(ContactLayer::EntitySmallObject);
    body->enableContactLayer(ContactLayer::EntityGroundObject);
    body->enableContactLayer(ContactLayer::EntityNPC);
    body->enableContactLayer(ContactLayer::EntityRope);
    body->enableContactLayer(ContactLayer::EntityTree);
    body->enableContactLayer(ContactLayer::EntityNPC_NoHitPlayer);
    body->enableContactLayer(ContactLayer::EntityHitOnlyGround);
}

void AirWallCollisionSpecify::sub_7100616700(ksys::phys::RigidBody* body) {
    const u32 mask = ksys::phys::orEntityGroundHitMask(0, ksys::phys::GroundHit::NPC);
    body->setGroundHitMask(body->getContactLayer(), mask);
}

}  // namespace uking::behavior
