#include "Game/AI/Action/actionEquipedWeaponChild.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"

namespace uking::action {

EquipedWeaponChild::EquipedWeaponChild(const InitArg& arg) : BindAction(arg) {}

void EquipedWeaponChild::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    _e0 = mActor->getScale();
    sead::Vector3f scale;
    sub_7100E14D6C(&scale);
    mActor->setScale(scale);
}

void EquipedWeaponChild::leave_() {
    BindAction::leave_();
    mActor->setScale(_e0);
}

void EquipedWeaponChild::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mIsChangeScale_s, "IsChangeScale");
}

void EquipedWeaponChild::sub_7100E14D6C(sead::Vector3f* scale) {
    if (*mIsChangeScale_s) {
        auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(
            sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()));
        if (weapon && weapon->isWeaponType3() && weapon->m142()) {
            weapon->m224(scale);
            return;
        }
    }
    *scale = sead::Vector3f::ones;
}

void EquipedWeaponChild::m32() {}

ksys::act::Actor* EquipedWeaponChild::m33() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(
        sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()));
    if (!weapon)
        return nullptr;
    return weapon->getParentActor();
}

}  // namespace uking::action
