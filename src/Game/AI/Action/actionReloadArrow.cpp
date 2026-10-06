#include "Game/AI/Action/actionReloadArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: scheduling of the param pointer stores around the vtable store
ReloadArrow::ReloadArrow(const InitArg& arg) : ActionEx(arg) {}

ReloadArrow::~ReloadArrow() = default;

// NON_MATCHING: the original copies the angular speed through an integer register (stp w-pairs for the
// VFRVec3f stores); we keep it in an FP register
void ReloadArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("ArrowReload", false, 0, 0, -1.0f);
    sub_71005D787C(mActor, *mParams.mWeaponIdx_s, act::Unk_71002eda38(3));

    const f32 speed = mActor->getVelocity().length();
    _40.value = speed;
    _40.prev_value = speed;
    const sead::Vector3f angular_velocity(0, mActor->getAngVelocity().y, 0);
    _70 = angular_velocity.length();
    _4c.value.set(angular_velocity);
    _4c.prev_value.set(angular_velocity);
}

void ReloadArrow::leave_() {
    sub_71005D787C(mActor, *mParams.mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ReloadArrow::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void ReloadArrow::sub_710022A9E4() {
    sead::Vector3f to_target = *mParams.mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    to_target.y = 0.0f;
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);

    const f32 rot_speed = *mParams.mRotSpeed_s;
    ksys::VFR::lerp(&_70, angle, 0.15f, rot_speed, sead::Mathf::deg2rad(1.0f));
    _70 = sead::Mathf::clamp(_70, -rot_speed, rot_speed);

    sead::Vector3f angular_velocity = axis;
    angular_velocity *= _70;
    _4c.chase(angular_velocity, rot_speed);
    _4c.updateStats();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(_4c.value * 30.0f);
}

void ReloadArrow::calc_() {
    _40 *= *mParams.mStopSpeedRatio_s;
    _40.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        sub_710072C1B4(controller, front);
        controller->sub_7100F5E7F0(_40.value * 30.0f);
    }
    sub_710022A9E4();
    sub_71005D787C(mActor, *mParams.mWeaponIdx_s, act::Unk_71002eda38(3));
    if (isFinishedAS(0, 0))
        setFinished();
}

bool ReloadArrow::isChangeable() const {
    return false;
}

}  // namespace uking::action
