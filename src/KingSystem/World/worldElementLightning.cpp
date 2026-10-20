#include "KingSystem/World/worldElementLightning.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
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

// NON_MATCHING: scheduling of the matrix and param stores (same as ElementSpark::m29).
bool ElementLightningFire::m29(const ElementName& name, sead::Heap* heap) {
    sead::Matrix34f mtx;
    mtx.makeT(mArg.position);

    ksys::phys::SphereParam param;
    param.name = "LightningFire";
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.radius = mHolder->_8->shock_wave_speed.ref();
    param.motion_type = ksys::phys::MotionType::Keyframed;
    mRigidBody2 = ksys::phys::SphereRigidBody::make(&param, heap);
    if (!mRigidBody2)
        return false;

    mRigidBody2->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    setRigidBody(mRigidBody2, true);
    ksys::act::Chemical::sub_7100D8CD24(mHolder, false);
    return true;
}

// NON_MATCHING: scheduling of the matrix and param stores (same as ElementSpark::m29); the original
// branches on the water flag where ours uses csel.
bool ElementLightningShockwave::m29(const ElementName& name, sead::Heap* heap) {
    sead::Matrix34f mtx;
    mtx.makeT(mArg.position);

    ksys::phys::SphereParam param;
    param.name = "LightningShockwave";
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.radius = mHolder->_8->shock_wave_speed.ref();
    param.motion_type = ksys::phys::MotionType::Keyframed;
    mRigidBody2 = ksys::phys::SphereRigidBody::make(&param, heap);
    if (!mRigidBody2)
        return false;

    mRigidBody2->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    setRigidBody(mRigidBody2, true);
    auto* actor = ksys::act::Reaction::instance()->_38;
    Unk_71012419b4 xlink;
    const char* xlink_name = "Chemical_Lightning";
    if (mArg.flags & 2)
        xlink_name = "Chemical_Lightning_Water";
    xlinkSearchAndEmit(actor, xlink_name, 2, &xlink);
    if (xlink.sub_7101241B6C())
        xlink.sub_7101241A44(mtx);
    ksys::act::Chemical::sub_7100D8CD24(mHolder, false);
    return true;
}
