#include "Game/AI/Action/actionUnarmedAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
UnarmedAttack::UnarmedAttack(const InitArg& arg) : ActionEx(arg) {}

UnarmedAttack::~UnarmedAttack() = default;

void UnarmedAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void UnarmedAttack::leave_() {
    ActionEx::leave_();
}

void UnarmedAttack::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtRigidBodyName_s, "AtRigidBodyName");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotAngle_s, "RotAngle");
    getStaticParam(&mSpeedStopRatio_s, "SpeedStopRatio");
    getStaticParam(&mRotSpeedStopRatio_s, "RotSpeedStopRatio");
    getStaticParam(&mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
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

}  // namespace uking::action
