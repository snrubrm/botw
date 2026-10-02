#include "Game/AI/Action/actionRagdoll.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Ragdoll::Ragdoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Ragdoll::~Ragdoll() = default;

bool Ragdoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Ragdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Ragdoll::leave_() {
    ksys::act::ai::Action::leave_();
}

void Ragdoll::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mInWaterDownTime_s, "InWaterDownTime");
    getStaticParam(&mForceFinishTime_s, "ForceFinishTime");
    getStaticParam(&mOnGroundDownTime_s, "OnGroundDownTime");
    getStaticParam(&mStartUpdateFriction_s, "StartUpdateFriction");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mGetUpGroundAngle_s, "GetUpGroundAngle");
    getStaticParam(&mForceEndWaterDepth_s, "ForceEndWaterDepth");
    getStaticParam(&mIsWaitAS_s, "IsWaitAS");
    getStaticParam(&mIsItemDrop_s, "IsItemDrop");
    getStaticParam(&mIsCheckVibrate_s, "IsCheckVibrate");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mStableASName_s, "StableASName");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Ragdoll::calc_() {
    ksys::act::ai::Action::calc_();
}

bool Ragdoll::m36() {
    if (m37() >= 1 && _c0.x < 0.0f)
        return true;
    return false;
}

void Ragdoll::m39() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F62CA8(true);
    }
}

s32 Ragdoll::m40() {
    return *mTime_s;
}

}  // namespace uking::action
