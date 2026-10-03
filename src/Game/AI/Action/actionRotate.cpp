#include "Game/AI/Action/actionRotate.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void Rotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
