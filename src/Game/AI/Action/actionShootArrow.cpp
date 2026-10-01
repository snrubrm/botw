#include "Game/AI/Action/actionShootArrow.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ShootArrow::ShootArrow(const InitArg& arg) : ActionEx(arg) {}

ShootArrow::~ShootArrow() = default;

void ShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    m32();
    auto* actor = mActor;
    const sead::Vector3f vel = actor->getVelocity();
    const f32 speed = vel.length();
    _78.value = speed;
    _78.prev_value = speed;
    sead::Vector3f ang_vel = actor->getAngVelocity();
    ang_vel.x = 0;
    ang_vel.z = 0;
    _a8 = ang_vel.length();
    _84.value = ang_vel;
    _84.prev_value = ang_vel;
    _ac = false;
}

void ShootArrow::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mASName_s, "ASName");
}

void ShootArrow::calc_() {
    ActionEx::calc_();
}

bool ShootArrow::isChangeable() const {
    return false;
}

void ShootArrow::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
