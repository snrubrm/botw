#include "Game/AI/Action/actionDungeonRotateBase.h"
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2Handle.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DungeonRotateBase::DungeonRotateBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateBase::~DungeonRotateBase() {
    if (_a0) {
        delete _a0;
        _a0 = nullptr;
    }
    if (_a8) {
        delete _a8;
        _a8 = nullptr;
    }
}

bool DungeonRotateBase::init_(sead::Heap* heap) {
    _90 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_98, "FieldBodyGroup"))
        _98 = -1;
    _7c = *mInitDgnPriority_m;
    _84 = _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    _a0 = new (heap) xlink2::Handle;
    _a8 = new (heap) xlink2::Handle;
    return true;
}

void DungeonRotateBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonRotateBase::loadParams_() {
    getStaticParam(&mRotateAxisIndex_s, "RotateAxisIndex");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
    getMapUnitParam(&mVelocityControlRate_m, "VelocityControlRate");
    getMapUnitParam(&mAngleVelocityControlAccelDeg_m, "AngleVelocityControlAccelDeg");
}

void DungeonRotateBase::calc_() {
    ksys::act::ai::Action::calc_();
}

void DungeonRotateBase::m9() {
    _90 = mActor->getFieldBodyGroup();
    _7c = *mInitDgnPriority_m;
    _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
}

float DungeonRotateBase::m32() {
    _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    return _88;
}

// NON_MATCHING: the original loads mActor before _88 (scheduling)
void DungeonRotateBase::m33() {
    f32 speed = _88;
    if (mActor->checkVelocityControlSignal())
        speed *= *mVelocityControlRate_m;
    _84 = speed;
}

void DungeonRotateBase::m34(f32 x) {
    _8c = sead::Mathf::abs(x);
}

}  // namespace uking::action
