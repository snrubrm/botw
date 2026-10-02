#include "Game/AI/aiUnk_7100736460.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

bool sub_7100736460(ksys::act::BaseProcLink* link) {
    return ksys::act::hasTag(link, ksys::act::tags::ExplosivesEnemyAI);
}

bool sub_710073646C(ksys::act::BaseProcLink* link) {
    return ksys::act::hasTag(link, ksys::act::tags::Explosive);
}
