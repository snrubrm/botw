#include "Game/AI/Action/actionDieAnmKnockBack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DieAnmKnockBack::DieAnmKnockBack(const InitArg& arg) : SmallDamageBase(arg) {}

DieAnmKnockBack::~DieAnmKnockBack() = default;

void DieAnmKnockBack::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710072BB28(mActor);
    if (*mIsDropWeapon_s) {
        sead::Vector3f velocity = sead::Vector3f::ey;
        velocity *= *mWeaponDropSpeedY_s;
        sub_71005D8748(mActor, velocity, true, false, nullptr, false);
    }
}

void DieAnmKnockBack::leave_() {
    SmallDamageBase::leave_();
}

void DieAnmKnockBack::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mASName_s, "ASName");
}

void DieAnmKnockBack::calc_() {
    SmallDamageBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

bool DieAnmKnockBack::m36() {
    return false;
}

}  // namespace uking::action
