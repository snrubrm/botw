#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

MagneShaftRootBase::MagneShaftRootBase(const InitArg& arg) : MagneStickRoot(arg) {}

MagneShaftRootBase::~MagneShaftRootBase() = default;

bool MagneShaftRootBase::init_(sead::Heap* heap) {
    return MagneStickRoot::init_(heap);
}

void MagneShaftRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneStickRoot::enter_(params);
}

void MagneShaftRootBase::calc_() {
    MagneStickRoot::calc_();
}

void MagneShaftRootBase::leave_() {
    MagneStickRoot::leave_();
}

void MagneShaftRootBase::loadParams_() {
    MagneStickRoot::loadParams_();
}

void MagneShaftRootBase::m50() {
    if (mActor) {
        if (auto* body = m52())
            body->enableGroundCollision(false);
    }
}

void MagneShaftRootBase::m51() {
    if (mActor) {
        if (auto* body = m52())
            body->enableGroundCollision(true);
    }
}

}  // namespace uking::ai
