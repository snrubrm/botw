#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"

namespace ksys::act {

ActorWeapons::ActorWeapons(Actor* actor) : mActor(actor) {}

ActorWeapons::~ActorWeapons() = default;

WeaponBase* ActorWeapons::getEquippedWeapon(int idx) const {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (!weapon)
        return nullptr;
    return weapon->isCalc() ? weapon : nullptr;
}

}  // namespace ksys::act
