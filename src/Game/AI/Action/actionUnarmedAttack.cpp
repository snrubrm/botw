#include "Game/AI/Action/actionUnarmedAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
UnarmedAttack::UnarmedAttack(const InitArg& arg) : ActionEx(arg) {}

void UnarmedAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void UnarmedAttack::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mParams.mAtRigidBodyName_s))
        sub_71007A2D34(body);
    sub_71005DA114(mActor, &_70);
}

void UnarmedAttack::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mParams.mASName_s, "ASName");
    getStaticParam(&mParams.mAtRigidBodyName_s, "AtRigidBodyName");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotAngle_s, "RotAngle");
    getStaticParam(&mParams.mSpeedStopRatio_s, "SpeedStopRatio");
    getStaticParam(&mParams.mRotSpeedStopRatio_s, "RotSpeedStopRatio");
    getStaticParam(&mParams.mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mParams.mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
}

void UnarmedAttack::calc_() {
    ActionEx::calc_();
}

bool UnarmedAttack::isChangeable() const {
    return false;
}

int UnarmedAttack::m32() {
    return 16384;
}

f32 UnarmedAttack::m33() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

void UnarmedAttack::m34() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mParams.mAtRigidBodyName_s)) {
        sub_71007A2B64(body, nullptr);
        sub_71007A3258(body, nullptr);
    }
}

}  // namespace uking::action
