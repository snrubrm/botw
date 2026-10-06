#include "Game/AI/Action/actionStalEnemyBlownOff.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"

bool sub_71006F562C(ksys::phys::CharacterController* controller);

namespace uking::action {

StalEnemyBlownOff::StalEnemyBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalEnemyBlownOff::~StalEnemyBlownOff() = default;

void StalEnemyBlownOff::sub_71002749B4() {
    auto* controller = mActor->getCharacterController();
    if (!controller || sub_71006F562C(controller))
        return;
    const f32 current = controller->get110();
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    f32 step;
    if (_16e)
        step = delta * 0.15f;
    else
        step = delta * 0.03;
    controller->sub_7100F5EEB8(sead::Mathf::clamp(current + step, 0.0f, 1.0f));
}

// NON_MATCHING: the original loads WeaponDropSpeedXZ into a callee-saved register before the sqrt NaN
// check call (d8) and stores the two zero components in a different order; same instructions otherwise.
void StalEnemyBlownOff::sub_710027588C(sead::Vector3f* velocity) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && !sead::Mathf::equalsEpsilon(*mWeaponDropSpeedXZ_s, 0.0f)) {
        actor->sub_71006DD908(velocity);
        velocity->y = 0.0f;
        const f32 length = velocity->length();
        const f32 speed = *mWeaponDropSpeedXZ_s;
        if (length > 0.0f)
            *velocity *= speed / length;
    } else {
        velocity->x = 0.0f;
        velocity->z = 0.0f;
    }
    velocity->y = *mWeaponDropSpeedY_s;
}

void StalEnemyBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StalEnemyBlownOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void StalEnemyBlownOff::loadParams_() {
    getStaticParam(&mDownTimeBase_s, "DownTimeBase");
    getStaticParam(&mDownTimeRand_s, "DownTimeRand");
    getStaticParam(&mRecoverTimer_s, "RecoverTimer");
    getStaticParam(&mHeadShotSpeed_s, "HeadShotSpeed");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mHeadSpeedRate_s, "HeadSpeedRate");
    getStaticParam(&mMinHeadSpeedY_s, "MinHeadSpeedY");
    getStaticParam(&mMinHeadSpeedXZ_s, "MinHeadSpeedXZ");
    getStaticParam(&mHeadShotUseAddVec_s, "HeadShotUseAddVec");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mDisableBoneName_s, "DisableBoneName");
    getStaticParam(&mEnableConstraintName_s, "EnableConstraintName");
    getStaticParam(&mUseRagConName_s, "UseRagConName");
    getStaticParam(&mBlownOffASName_s, "BlownOffASName");
    getStaticParam(&mPreUniteASName_s, "PreUniteASName");
    getStaticParam(&mUniteASName_s, "UniteASName");
    getStaticParam(&mDieASName_s, "DieASName");
    getStaticParam(&mHeadRagdollRigidNames_s, "HeadRagdollRigidNames");
    getStaticParam(&mArmRagdollRigidNames_s, "ArmRagdollRigidNames");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getStaticParam(&mHeadShotAddVec_s, "HeadShotAddVec");
    getStaticParam(&mHeadRotateOffset_s, "HeadRotateOffset");
}

void StalEnemyBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

bool StalEnemyBlownOff::handleMessage_(const ksys::Message* message) {
    return false;
}

}  // namespace uking::action
