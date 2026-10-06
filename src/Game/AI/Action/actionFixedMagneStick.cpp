#include "Game/AI/Action/actionFixedMagneStick.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

FixedMagneStick::FixedMagneStick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FixedMagneStick::~FixedMagneStick() {
    if (_38) {
        ksys::phys::Constraint::destroy(_38);
        _38 = nullptr;
    }
}

bool FixedMagneStick::init_(sead::Heap* heap) {
    m32(heap);
    return true;
}

void FixedMagneStick::m32(sead::Heap* heap) {
    if (!mActor)
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    ksys::phys::FixedCs::Param param;
    param.body_a = body;
    _38 = ksys::phys::FixedCs::make(param, heap);
}

void FixedMagneStick::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    _58 = false;
    _59 = false;
}

void FixedMagneStick::leave_() {
    mActor->emitBasicSigOff();
    if (_38)
        _38->sub_7100F6A074();
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
}

void FixedMagneStick::loadParams_() {
    getMapUnitParam(&mGrabbedMagneReleaseTime_m, "GrabbedMagneReleaseTime");
    getAITreeVariable(&mMagneStickLength_a, "MagneStickLength");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

void FixedMagneStick::calc_() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;
    if (!_59) {
        _59 = m33();
        if (_59) {
            const f32 time = sead::Mathf::clampMin(*mGrabbedMagneReleaseTime_m, 1.0f);
            _4c = time;
            _40 = ksys::Timer(time, time);
            actor->emitBasicSigOn();
        }
        if (!_59) {
            if (actor->get6b8())
                actor->get6b8()->_8b = 2;
            return;
        }
    }
    if (!(_40.value <= sead::Mathf::epsilon())) {
        _40.update();
    } else if (!_58) {
        if (auto* scene = GameSceneSubsys5::instance()) {
            scene->sub_7100905C70();
            body->x_114(true);
            body->setMagneMassScalingFactor(30.0f);
        }
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        body->setLinearDamping(_50);
        body->setAngularDamping(_54);
        mFlags.set(Flag::Changeable);
        _58 = true;
    }
    if (actor->get6b8())
        actor->get6b8()->_8b = 2;
}

}  // namespace uking::action
