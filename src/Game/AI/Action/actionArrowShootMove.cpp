#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ArrowShootMove::ArrowShootMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ArrowShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ArrowShootMove::leave_() {
    if (!_149)
        sub_71000A331C();

    if (_138) {
        _138->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        _138->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        sub_71007A2D34(_138);
    }
}

void ArrowShootMove::loadParams_() {
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mFirstSpeed_d, "FirstSpeed");
    getDynamicParam(&mAccel_d, "Accel");
    getDynamicParam(&mAimSpeed_d, "AimSpeed");
    getDynamicParam(&mFallAccel_d, "FallAccel");
    getDynamicParam(&mFallAimSpeed_d, "FallAimSpeed");
    getDynamicParam(&mGravity_d, "Gravity");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAtPoint_d, "AtPoint");
    getDynamicParam(&mAtRange_d, "AtRange");
    getDynamicParam(&mAtImpulse_d, "AtImpulse");
    getDynamicParam(&mAtImpact_d, "AtImpact");
    getDynamicParam(&mRelativeVel_d, "RelativeVel");
    getDynamicParam(&mAtAttr_d, "AtAttr");
    getStaticParam(&mFallSpeedRatioByRange_s, "FallSpeedRatioByRange");
    getDynamicParam(&mAtMinDamage_d, "AtMinDamage");
}

void ArrowShootMove::calc_() {
    ksys::act::ai::Action::calc_();
}

float ArrowShootMove::m32() {
    return 0.5f;
}

bool ArrowShootMove::m35(const ksys::act::ActorConstDataAccess& accessor) {
    return false;
}

void ArrowShootMove::m36(bool* out, const ksys::act::ActorConstDataAccess& accessor) {}

void ArrowShootMove::m39(sead::Vector3f* out) {
    *out = _e4;
}

bool ArrowShootMove::m40() {
    if (*mAtRange_d <= 10.0f)
        return true;
    sead::Vector3f diff = _11c;
    diff -= mActor->getMtx().getTranslation();
    return diff.length() >= *mAtRange_d;
}

f32 ArrowShootMove::m41() {
    return 0.0f;
}

void ArrowShootMove::m42() {}

}  // namespace uking::action
