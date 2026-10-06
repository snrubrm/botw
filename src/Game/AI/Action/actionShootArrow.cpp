#include "Game/AI/Action/actionShootArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

ShootArrow::ShootArrow(const InitArg& arg) : ActionEx(arg) {}

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

void ShootArrow::sub_710024E90C() {
    _78 *= *mStopSpeedRatio_s;
    _78.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        sub_710072C1B4(controller, mActor->getMtx().getBase(2));
        controller->sub_7100F5E7F0(_78.value * 30.0f);
    }
}

void ShootArrow::sub_710024E994() {
    _84 *= *mStopRotSpeedRatio_s;
    _84.updateStats();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(_84.value * 30.0f);
}

void ShootArrow::m33(const sead::Vector3f& pos, const sead::Vector3f* pos2) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100016494();
    sub_71005D80FC(mActor, *mWeaponIdx_s, pos, 0, 1.0f, pos2, nullptr);
}

void ShootArrow::m34() {
    sub_710024E90C();
    sub_710024E994();
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
