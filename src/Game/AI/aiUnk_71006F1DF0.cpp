#include "Game/AI/aiUnk_71006F1DF0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

bool sub_71006F1DF0(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (mgr && actor->m132() && !ksys::act::hasTag(actor, ksys::act::tags::AnimalTypeDomestic) &&
        mgr->isNonAutoPlacement(pos, false)) {
        return true;
    }
    return false;
}
