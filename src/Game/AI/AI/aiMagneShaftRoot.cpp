#include "Game/AI/AI/aiMagneShaftRoot.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

MagneShaftRoot::MagneShaftRoot(const InitArg& arg) : MagneShaftRootBase(arg) {}

MagneShaftRoot::~MagneShaftRoot() {
    if (_a0) {
        ksys::phys::Constraint::destroy(_a0);
        _a0 = nullptr;
    }
}

bool MagneShaftRoot::init_(sead::Heap* heap) {
    if (!MagneShaftRootBase::init_(heap))
        return false;
    auto* actor = mActor;
    if (!actor)
        return true;
    auto* body = actor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0");
    if (!body)
        return true;
    auto* main_body = actor->getMainBody();
    if (!main_body)
        return true;
    ksys::phys::FixedCs::Param param;
    param.body_a = main_body;
    param.body_b = body;
    _a0 = ksys::phys::FixedCs::make(param, heap);
    return true;
}

void MagneShaftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0"))
            body->addToWorld();
    }
    if (auto* fixed = sead::DynamicCast<ksys::phys::FixedCs>(_a0)) {
        sead::Matrix34f mtx;
        mtx.makeIdentity();
        fixed->sub_7100F6D6D8(mtx, mtx);
        fixed->sub_7100F69FF0();
    }
}

void MagneShaftRoot::calc_() {
    MagneShaftRootBase::calc_();
}

void MagneShaftRoot::leave_() {
    MagneShaftRootBase::leave_();
    if (_a0 && (_a0->_50 & 1))
        _a0->sub_7100F6A074();
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0"))
            body->removeFromWorld();
    }
}

void MagneShaftRoot::loadParams_() {
    MagneShaftRootBase::loadParams_();
}

void MagneShaftRoot::m50() {
    MagneShaftRootBase::m50();
    if (!mActor)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    if (auto* gear_mgr = GearMgr::instance())
        physics->sub_7100FBDFA4(gear_mgr->_1050);
}

ksys::phys::RigidBody* MagneShaftRoot::m52() {
    if (!mActor)
        return nullptr;
    return mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0");
}

void MagneShaftRoot::m51() {
    MagneShaftRootBase::m51();
    if (!mActor)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    physics->sub_7100FBDFA4(physics->get178(0));
    physics->sub_7100FBDFA4(physics->get178(1));
}

}  // namespace uking::ai
