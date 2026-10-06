#include "Game/AI/Action/actionEquipedOptionalWeaponAction.h"
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EquipedOptionalWeaponAction::EquipedOptionalWeaponAction(const InitArg& arg) : BindAction(arg) {
    _38._98 = 0;
}

void EquipedOptionalWeaponAction::m32() {}

ksys::act::Actor* EquipedOptionalWeaponAction::m33() {
    if (auto* weapon = sead::DynamicCast<act::OptionalWeapon>(mActor))
        return sead::DynamicCast<ksys::act::Actor>(weapon->_840.getProc(nullptr, nullptr));
    return nullptr;
}

}  // namespace uking::action
