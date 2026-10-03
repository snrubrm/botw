#include "Game/AI/AI/aiMagneSliderBlockRootThunder.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
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
    if (!MagneShaftRootBase::init_(heap))
        return false;
    auto* actor = mActor;
    if (!actor)
        return true;
    auto* body = actor->findPhysicsBodyByName("BodyParts_00", "Body");
    if (!body)
        return true;
    if (auto* info = body->getContactPointInfo())
        info->setContactCallback(&_a8);
    auto* main_body = actor->getMainBody();
    if (!main_body)
        return true;
    ksys::phys::FixedCs::Param param;
    param.body_a = main_body;
    param.body_b = body;
    _a0 = ksys::phys::FixedCs::make(param, heap);
    return true;
}

void MagneSliderBlockRootThunder::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
    if (mActor) {
        if (auto* body = mActor->findPhysicsBodyByName("BodyParts_00", "Body")) {
            body->addToWorld();
            sead::Vector3f dir;
            body->getTransform().getBase(dir, 0);
            _a8._8 = dir;
        }
    }
    if (auto* fixed = sead::DynamicCast<ksys::phys::FixedCs>(_a0)) {
        sead::Matrix34f mtx;
        mtx.makeIdentity();
        fixed->sub_7100F6D6D8(mtx, mtx);
        fixed->sub_7100F69FF0();
    }
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
