#include "Game/AI/Action/actionEquipedWeaponChild.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"

namespace uking::action {

EquipedWeaponChild::EquipedWeaponChild(const InitArg& arg) : BindAction(arg) {}

void EquipedWeaponChild::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void EquipedWeaponChild::leave_() {
    BindAction::leave_();
}

void EquipedWeaponChild::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mIsChangeScale_s, "IsChangeScale");
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
