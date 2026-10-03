#include "Game/AI/Action/actionReloadArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

void ReloadArrow::calc_() {
    ActionEx::calc_();
}

bool ReloadArrow::isChangeable() const {
    return false;
}

}  // namespace uking::action
