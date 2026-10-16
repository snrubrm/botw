#include "KingSystem/World/worldElementLightning.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::world {

// NON_MATCHING: ray-query result registers and comparison scheduling differ.
ElementLightningShockwave* sub_71012FDA7C(ElementLightningCreateArg arg, bool check_collision) {
    if (check_collision) {
        f32 water_height = arg.position.y - 10.0f;
        {
            phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
            query.enableLayer(phys::ContactLayer::EntityWater);
            sead::Vector3f start = arg.position + sead::Vector3f::ey * 10.0f;
            const sead::Vector3f end = arg.position - sead::Vector3f::ey * 10.0f;
            query.setStartAndEnd(start, end);
            if (query.worldRayCast(phys::ContactLayerType::Entity)) {
                query.getHitPosition(&start);
                water_height = start.y;
            }
        }
        bool ground_hit;
        f32 ground_height;
        {
            phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
            query.enableLayer(phys::ContactLayer::EntityGround);
            query.enableLayer(phys::ContactLayer::EntityGroundSmooth);
            query.enableLayer(phys::ContactLayer::EntityGroundObject);
            sead::Vector3f start = arg.position + sead::Vector3f::ey * 10.0f;
            const sead::Vector3f end = arg.position - sead::Vector3f::ey * 10.0f;
            query.setStartAndEnd(start, end);
            ground_hit = query.worldRayCast(phys::ContactLayerType::Entity);
            if (ground_hit) {
                query.getHitPosition(&start);
                ground_height = start.y;
            }
        }
        if (!ground_hit || water_height > ground_height)
            arg.flags |= 2;
    }
    auto* holder = Manager::instance()->getChemicalMgr()->_ae8;
    if (holder)
        return holder->sub_71012FE4B4(&arg);
    return nullptr;
}

ElementLightningFire* sub_71012FDF24(const ElementLightningCreateArg* arg) {
    auto* holder = Manager::instance()->getChemicalMgr()->_ae8;
    if (holder)
        return holder->sub_71012FE6E0(arg);
    return nullptr;
}

}  // namespace ksys::world

ElementLightningShockwave::~ElementLightningShockwave() {
    if (mRigidBody2) {
        delete mRigidBody2;
        mRigidBody2 = nullptr;
    }
}

void ElementLightningShockwave::m33(bool a, bool fixed) {
    if (mRigidBody2)
        mRigidBody2->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

ElementLightningFire::~ElementLightningFire() {
    if (mRigidBody2) {
        delete mRigidBody2;
        mRigidBody2 = nullptr;
    }
}

void ElementLightningFire::m33(bool a, bool fixed) {
    if (mRigidBody2)
        mRigidBody2->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}
