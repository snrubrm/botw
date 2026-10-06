#include "Game/AI/aiUnk_7100736460.h"
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
