#include "Game/Actor/Action/actionDgnObj_DLC_CogWheel_Rotate.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/Constraint/physHingeCs.h"

namespace uking::action {

// NON_MATCHING: store merging of the two quaternions at 0x6c / 0x7c differs.
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

// NON_MATCHING: axis copies, quaternion inverse operands and zero-velocity stores differ.
void DgnObj_DLC_CogWheel_Rotate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* gear = GearMgr::instance();
    if (!gear)
        return;
    const f32 ratio = *mGearRatio_m;
    _58 = ratio > 0.0f ? 1.0f / ratio : 0.0f;
    _54 = *mIsClockWiseRotation_m ? 1.0f : -1.0f;
    auto* actor = mActor;
    if (actor) {
        _60 = sead::Vector3f::ez;
        if (auto* body = actor->getMainBody()) {
            for (s32 i = 0; i < actor->getConstraints().size(); ++i) {
                auto* constraint = actor->getConstraints().mConstraints[i];
                if (constraint && constraint->_10 == 3) {
                    if (auto* hinge = sead::DynamicCast<ksys::phys::HingeCs>(constraint))
                        _60 = hinge->sub_7100F6DF30();
                }
            }
            _6c = body->getRotation();
            _7c.setInverse(_6c);
            body->changeMotionType(_9c);
            body->setAngularVelocity({0.0f, 0.0f, 0.0f}, sead::Mathf::epsilon());
            _a0 = !body->hasFlag(ksys::phys::RigidBody::Flag::_2000000);
            body->clearFlag2000000(false);
            _4c = gear->_109c;
        }
    }
    _48 = 0;
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
