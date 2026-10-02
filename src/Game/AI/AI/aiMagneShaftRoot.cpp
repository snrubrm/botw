#include "Game/AI/AI/aiMagneShaftRoot.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
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
    return MagneShaftRootBase::init_(heap);
}

void MagneShaftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
}

void MagneShaftRoot::calc_() {
    MagneShaftRootBase::calc_();
}

void MagneShaftRoot::leave_() {
    MagneShaftRootBase::leave_();
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
