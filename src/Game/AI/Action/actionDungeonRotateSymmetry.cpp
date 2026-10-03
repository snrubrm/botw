#include "Game/AI/Action/actionDungeonRotateSymmetry.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiXlinkHandle.h"

namespace uking::action {

DungeonRotateSymmetry::DungeonRotateSymmetry(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateSymmetry::~DungeonRotateSymmetry() {
    if (_88) {
        delete _88;
        _88 = nullptr;
    }
}

bool DungeonRotateSymmetry::init_(sead::Heap* heap) {
    _88 = new (heap) xlink2::HandleSLink;
    return true;
}

void DungeonRotateSymmetry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateSymmetry::leave_() {
    if (_88)
        xlink::fade(*_88, -1);
}

void DungeonRotateSymmetry::loadParams_() {
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

void DungeonRotateSymmetry::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
