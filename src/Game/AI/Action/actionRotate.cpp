#include "Game/AI/Action/actionRotate.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

Rotate::Rotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Rotate::~Rotate() = default;

bool Rotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Rotate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    switch (*mRotAxis_m) {
    case 0:
        _40.set(sead::Vector3f::ex);
        break;
    case 1:
        _40.set(sead::Vector3f::ey);
        break;
    case 2:
        _40.set(sead::Vector3f::ez);
        break;
    }

    const f32 angle = sead::Mathf::deg2rad(*mTiltAngle_m);
    if (*mIsReturn_s) {
        _58.set(sead::Vector3f::zero);
        _4c = _58 + _40 * angle;
    } else {
        _4c.set(sead::Vector3f::zero);
        _58 = _4c + _40 * angle;
        actor->emitBasicSigOn();
        actor->setRevivalFlagForUsed(true);
    }
}

void Rotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void Rotate::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getMapUnitParam(&mRotAxis_m, "RotAxis");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
}

// NON_MATCHING: only the `_4c = _58` copy differs (the original copies z first through two address registers;
// `_4c.set(_58)` gives that order but hoists the address computations into the earlier loads).
void Rotate::calc_() {
    auto* actor = mActor;
    const f32 step = sead::Mathf::deg2rad(*mTiltAngularSpeed_m) * ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f dir = _58;
    dir -= _4c;
    const f32 length = dir.length();
    if (length <= step) {
        _4c = _58;
        setFinished();
    } else {
        dir *= 1.0f / length;
        _4c += dir * step;
    }
    if (auto* body = actor->getMainBody()) {
        sead::Matrix34f home;
        actor->getHomeMtx(&home);
        sead::Matrix34f rot;
        rot.makeR(_4c);
        home.setMul(home, rot);
        body->changePositionAndRotation(home, 1.1920929e-07f);
    }
}

}  // namespace uking::action
