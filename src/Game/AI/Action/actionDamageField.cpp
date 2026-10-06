#include "Game/AI/Action/actionDamageField.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

DamageField::DamageField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamageField::~DamageField() = default;

bool DamageField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// inline-only in the original; name is a guess: the same switch is inlined into enter_, calc_ and leave_.
inline const sead::SafeString& DamageField::getRigidSetName() const {
    switch (*mRigidSetName_s) {
    case 0:
        return ksys::act::getStr_Body();
    case 1:
        return ksys::act::getStr_GeneralSensor();
    default:
        return sead::SafeString::cEmptyString;
    }
}

void DamageField::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mIsUseCollisionInfo_s && *mIsChangeRigidWorldMode_s) {
        if (auto* body = mActor->findPhysicsBodyByName(getRigidSetName().cstr(),
                                                       mRigidBodyName_s.cstr()))
            body->addToWorld();
    }
    _60._18 = *mFieldType_s;
    mFlags.set(Flag::Changeable);
}

void DamageField::leave_() {
    if (!*mIsUseCollisionInfo_s && *mIsChangeRigidWorldMode_s) {
        if (auto* body = mActor->findPhysicsBodyByName(getRigidSetName().cstr(),
                                                       mRigidBodyName_s.cstr()))
            body->removeFromWorld();
    }
}

void DamageField::loadParams_() {
    getStaticParam(&mFieldType_s, "FieldType");
    getStaticParam(&mRigidSetName_s, "RigidSetName");
    getStaticParam(&mIsChangeRigidWorldMode_s, "IsChangeRigidWorldMode");
    getStaticParam(&mIsUseCollisionInfo_s, "IsUseCollisionInfo");
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
    getStaticParam(&mCollisionInfoName_s, "CollisionInfoName");
}

void DamageField::calc_() {
    auto* actor = mActor;
    if (*mIsUseCollisionInfo_s) {
        if (auto* physics = actor->getPhysics()) {
            const s32 idx = physics->findCollisionInfo(mCollisionInfoName_s.cstr());
            ksys::phys::CollisionInfo* info = nullptr;
            if (idx >= 0)
                info = physics->getCollisionInfoAt(idx);
            sub_7100E5DAC(info);
        }
    } else if (auto* body = actor->findPhysicsBodyByName(getRigidSetName().cstr(),
                                                          mRigidBodyName_s.cstr())) {
        sub_7100E5DAC(body->getCollisionInfo());
    }
}

// Sends message 0x8000084 to the actor of every body that collides with `info`.
void DamageField::sub_7100E5DAC(ksys::phys::CollisionInfo* info) {
    if (!info)
        return;
    if (info->getCollidingBodies().size() == 0)
        return;

    auto* bodies = info->getCollidingBodies().front();
    info->lock();
    for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
        if (auto* body = bodies->bodies[1]) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::getCollidedActorMaybe(&accessor, body);
            if (accessor.hasProc())
                _60.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }
    info->unlock();
}

}  // namespace uking::action
