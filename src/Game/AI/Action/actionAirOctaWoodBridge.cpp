#include "Game/AI/Action/actionAirOctaWoodBridge.h"
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

void AirOctaWoodBridgeUserTag::onImpulse(ksys::phys::RigidBody* body_a,
                                         ksys::phys::RigidBody* body_b, float impulse_a) {
    PhysicsUserTag::onImpulse(body_a, body_b, impulse_a);
    _18 = impulse_a;
}

AirOctaWoodBridge::AirOctaWoodBridge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaWoodBridge::~AirOctaWoodBridge() {
    if (auto* body = mActor->getMainBody())
        body->setUserTag(&mActor->mPhysicsUserTag);
}

bool AirOctaWoodBridge::init_(sead::Heap* heap) {
    mActor->mDrawDistanceFlags.set(2);
    return true;
}

void AirOctaWoodBridge::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        body->setUserTag(&_20);
        body->clearEntityMotionFlag4(true);
        body->clearEntityMotionFlag10(true);
        body->setMaxImpulse(0.0f);
    }
    sub_7100089F18();
}

void AirOctaWoodBridge::leave_() {}

void AirOctaWoodBridge::loadParams_() {}

// NON_MATCHING: the original also computes the (unused) length of each link's angular velocity
// (the sqrtf errno fallback survives); the discarded velocity getter calls are in the original.
void AirOctaWoodBridge::calc_() {
    if (_94)
        return;

    if (_90 > 0.0f)
        _90 -= ksys::VFR::instance()->getDeltaTime();
    if (_90 > 0.0f)
        return;

    auto* body = mActor->getMainBody();
    if (!body)
        return;

    const sead::Vector3f velocity = body->getLinearVelocity();
    const f32 speed = sead::Vector2f(velocity.x, velocity.z).length();
    const f32 speed_y = body->getLinearVelocity().y;
    body->getAngularVelocity();

    f32 max_link_speed = 0.0f;
    for (int i = 0; i < _40.size(); ++i) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(_40[i], &accessor)) {
            const sead::Vector3f& link_velocity = accessor.getVelocity();
            const f32 link_speed = sead::Vector2f(link_velocity.x, link_velocity.z).length();
            accessor.getVelocity();
            accessor.getAngVelocity();
            max_link_speed = sead::Mathf::max(link_speed, max_link_speed);
        }
    }

    const bool moving = speed >= 1.1f || _20._18 >= 1000.0f ||
                        sead::Mathf::abs(speed_y) >= 2.5f || max_link_speed >= 0.05f;
    if (!moving) {
        auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
        if (!actor || !actor->_a69)
            return;
    }

    auto& constraints = mActor->getConstraints();
    for (int i = 0; i < constraints.size(); ++i) {
        if (auto* constraint = constraints.mConstraints[i])
            constraint->sub_7100F6A074();
    }
    _94 = true;
}

void AirOctaWoodBridge::sub_7100089F18() {
    auto* object = mActor->getMapObject();
    if (!object)
        return;
    auto* link_data = object->getLinkData();
    if (!link_data)
        return;

    for (int i = 0; i < link_data->mLinksCs.links.size(); ++i) {
        if (_40.isFull())
            return;
        auto& link = link_data->mLinksCs.links[i];
        if (link.type >= ksys::map::MapLinkDefType::FixedCs &&
            link.type <= ksys::map::MapLinkDefType::RackAndPinionCs) {
            if (auto* proc_link = _40.emplaceBack()) {
                ksys::act::ActorConstDataAccess accessor;
                link.getObjectProcWithAccessor(accessor);
                if (accessor.hasProc())
                    accessor.linkAcquire(proc_link);
            }
        }
    }
}

}  // namespace uking::action
