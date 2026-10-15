#include "Game/Actor/aiUnk_71006F1DF0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/Physics/physMaterialMask.h"

bool sub_71006F1DF0(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* mgr = uking::AutoPlacementMgr::instance();
    if (mgr && actor->m132() && !ksys::act::hasTag(actor, ksys::act::tags::AnimalTypeDomestic) &&
        mgr->isNonAutoPlacement(pos, false)) {
        return true;
    }
    return false;
}

bool sub_71006F1E70(const ksys::phys::MaterialMask& mask) {
    return ((u64(1) << mask.getMaterial()) & 0x200a) != 0;
}
