#include "Game/AI/AI/aiMagneShaftRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

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

ksys::phys::RigidBody* MagneShaftRoot::m52() {
    if (!mActor)
        return nullptr;
    return mActor->findPhysicsBodyByName("BodyParts_00", "RigidBody_0");
}

}  // namespace uking::ai
