#include "Game/AI/Action/actionStalEnemyBlownOff.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
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

void StalEnemyBlownOff::sub_7100274D98() {
    if (_16d)
        return;
    auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!dynamic_actor)
        return;
    auto* ragdoll = dynamic_actor->getRagdollInstance();
    if (!ragdoll)
        return;
    const auto& mtx = mActor->getMtx();
    _164 = sead::Mathf::atan2(mtx.m[1][2], sead::Mathf::sqrt(mtx.m[0][2] * mtx.m[0][2] +
                                                            mtx.m[2][2] * mtx.m[2][2])) *
           sead::Mathf::rad2deg(1.0f);
    mActor->getASList()->x_6(9, 0, _164);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Matrix34f transform;
    controller->physicsXXXGetMtx_1(&transform);
    if (_160 >= 0 && ragdoll->getRigidBodies_()[_160]) {
        const sead::Vector3f center = ragdoll->getRigidBodies_()[_160]->getCenterOfMassInWorld();
        transform.m[0][3] = center.x;
        transform.m[1][3] = center.y;
        transform.m[2][3] = center.z;
    } else if (auto* handler = dynamic_actor->_868) {
        handler->sub_71006EE1F8(mPosBaseRagdollRbName_s);
        handler->sub_71006EDE54(&transform, mPosBaseRagdollRbName_s);
    }
    controller->sub_7100F5F938(transform);
}

void StalEnemyBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _16e = sub_71007271D4(actor);
    _1d8.reset();
    _160 = -1;
    if (auto* ragdoll = mActor->getRagdollInstance())
        _160 = ragdoll->getBoneIndexByName(mPosBaseRagdollRbName_s);
    if (auto* physics = actor->getPhysics()) {
        const int index = physics->sub_7100FBDA2C(mUseRagConName_s);
        if (index >= 0)
            _15c = index;
    }
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        if (dynamic_actor->_868)
            dynamic_actor->_868->sub_71006ED484();
    }
    if (!mBlownOffASName_s.isEmpty())
        playAS(mBlownOffASName_s.cstr(), true, 0, 0, -1.0f);
    if (auto* controller = actor->getCharacterController()) {
        _1e8.sub_710072AD1C(controller);
        _1e8._4.setDirect(0xe);
        _1e8.sub_710072AE20(controller);
        controller->sub_7100F60AE0();
        controller->sub_7100F62CA8(false);
        controller->sub_7100F63554(false);
        controller->mFlags.reset(8);
        if (!_16e) {
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityObject);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
        }
    }
    _16c = true;
    _16d = false;
    ksys::act::disableAttClient(actor, "LockOn");
    ksys::act::disableAttClient(actor, "Grab");
    _1a0 = sead::Vector3f::zero;
    _13c = 5.0f;
    _140 = 5.0f;
    _158 = 0;
    _144 = -1.0f;
    sub_7100273888();
    sub_710073FA90(&_170, actor);
    sub_71007A397C(actor);
    if (auto* physics = mActor->getPhysics()) {
        if (auto* ragdoll = physics->getRagdollInstance()) {
            ragdoll->setContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
            ragdoll->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            ragdoll->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
            ragdoll->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
            ragdoll->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
        }
    }
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
