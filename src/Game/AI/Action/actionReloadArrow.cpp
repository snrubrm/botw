#include "Game/AI/Action/actionReloadArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: scheduling of the param pointer stores around the vtable store
ReloadArrow::ReloadArrow(const InitArg& arg) : ActionEx(arg) {}

ReloadArrow::~ReloadArrow() = default;

void ReloadArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
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
