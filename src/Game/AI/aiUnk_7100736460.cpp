#include "Game/AI/aiUnk_7100736460.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

bool sub_7100736414(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_7100022ED8();
}

bool sub_7100736460(ksys::act::BaseProcLink* link) {
    return ksys::act::hasTag(link, ksys::act::tags::ExplosivesEnemyAI);
}

bool sub_710073646C(ksys::act::BaseProcLink* link) {
    return ksys::act::hasTag(link, ksys::act::tags::Explosive);
}

namespace dlc {
bool isPlayingOneHitObliteratorQuest() {
    return ksys::gdt::getFlag_BalladOfHeroes_Step02() && !ksys::gdt::getFlag_BalladOfHeroes_Step03();
}

bool isOneHitObliteratorActor(ksys::act::Actor* actor, bool a2) {
    if (!actor)
        return false;
    ksys::act::BaseProcLink link;
    link.acquire(actor, false);
    return isOneHitObliteratorBaseProcLink(&link, a2);
}

bool isOneHitObliteratorActorAccessor(const ksys::act::ActorConstDataAccess& accessor,
                                     bool check_active) {
    const auto& name = accessor.getName();
    if (name.isEmpty() || name != "Weapon_Sword_502")
        return false;
    return !check_active || isOneHitObliteratorActorActive(accessor);
}

// NON_MATCHING: failure paths share the scoped result instead of the native status flag.
bool isOneHitObliteratorActorActive(const ksys::act::ActorConstDataAccess& accessor) {
    bool active = false;
    if (accessor.isWeaponProfile()) {
        ksys::act::ActorConstDataAccess weapon;
        weapon.acquireActor(accessor);
        if (isPlayingOneHitObliteratorQuest() &&
            (ksys::StageInfo::sIsCDungeon || !hasEscapedOneHitObliteratorQuest(false))) {
            active = sub_71002F1000(weapon);
        }
    }
    return active;
}
}  // namespace dlc

bool hasAnimalTypeWolfOrBearTags(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    if (ksys::act::hasTag(actor, ksys::act::tags::AnimalTypeWolf) &&
        ksys::act::hasTag(link, ksys::act::tags::AnimalTypeWolf)) {
        return true;
    }
    if (ksys::act::hasTag(actor, ksys::act::tags::AnimalTypeBear) &&
        ksys::act::hasTag(link, ksys::act::tags::AnimalTypeBear)) {
        return true;
    }
    return false;
}
