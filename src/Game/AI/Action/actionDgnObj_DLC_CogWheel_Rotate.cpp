#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_Rotate.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// NON_MATCHING: store merging of the two quaternions at 0x6c / 0x7c (identical stores, different order/pairing)
DgnObj_DLC_CogWheel_Rotate::DgnObj_DLC_CogWheel_Rotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_Rotate::~DgnObj_DLC_CogWheel_Rotate() = default;

bool DgnObj_DLC_CogWheel_Rotate::init_(sead::Heap* heap) {
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            _9c = body->getMotionType();
    }
    if (auto* mgr = GearMgr::instance())
        mgr->sub_7100669AF8(*mTargetAngularDisplPerSec_s * 0.017453292f);
    return true;
}

void DgnObj_DLC_CogWheel_Rotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CogWheel_Rotate::leave_() {
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            body->clearFlag2000000(_a0);
    }
}

void DgnObj_DLC_CogWheel_Rotate::loadParams_() {
    getStaticParam(&mTargetAngularDisplPerSec_s, "TargetAngularDisplPerSec");
    getDynamicParam(&mIsRegisteredFrame_d, "IsRegisteredFrame");
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mIsClockWiseRotation_m, "IsClockWiseRotation");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_CogWheel_Rotate::calc_() {
    ksys::act::ai::Action::calc_();
}

void DgnObj_DLC_CogWheel_Rotate::m32() {
    auto* mgr = GearMgr::instance();
    if (!mgr)
        return;
    if (!(mgr->_10a4 & 1) && _48)
        return;
    if (mgr->_10b0[mgr->_2c ^ 1] & 1)
        playAS("Left", false, 0, 0, -1.0f);
    else
        playAS("Right", false, 0, 0, -1.0f);
}

}  // namespace uking::action
