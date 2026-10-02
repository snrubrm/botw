#include "Game/AI/AI/aiMagneSliderBlockRootThunder.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

bool Unk_7102406e88::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body->getContactLayer() == ksys::phys::ContactLayer::EntityGround) {
        if (sead::Mathf::abs(event.separating_normal->dot(_8)) < 0.9f) {
            *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
            return false;
        }
    }
    return true;
}

namespace uking::ai {

MagneSliderBlockRootThunder::MagneSliderBlockRootThunder(const InitArg& arg)
    : MagneShaftRootBase(arg) {}

MagneSliderBlockRootThunder::~MagneSliderBlockRootThunder() {
    if (_a0) {
        ksys::phys::Constraint::destroy(_a0);
        _a0 = nullptr;
    }
}

bool MagneSliderBlockRootThunder::init_(sead::Heap* heap) {
    return MagneShaftRootBase::init_(heap);
}

void MagneSliderBlockRootThunder::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
}

void MagneSliderBlockRootThunder::calc_() {
    MagneShaftRootBase::calc_();
}

void MagneSliderBlockRootThunder::leave_() {
    MagneShaftRootBase::leave_();
    if (_a0 && (_a0->_50 & 1))
        _a0->sub_7100F6A074();
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "Body"))
            body->removeFromWorld();
    }
}

void MagneSliderBlockRootThunder::loadParams_() {
    MagneShaftRootBase::loadParams_();
}

ksys::phys::RigidBody* MagneSliderBlockRootThunder::m52() {
    if (!mActor)
        return nullptr;
    return mActor->findPhysicsBodyByName("BodyParts_00", "Body");
}

}  // namespace uking::ai
