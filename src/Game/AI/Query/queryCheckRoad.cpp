#include "Game/AI/Query/queryCheckRoad.h"
#include <evfl/Query.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::query {

CheckRoad::CheckRoad(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRoad::~CheckRoad() = default;

int CheckRoad::doQuery() {
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    if (!npc)
        return 0;
    // NPCBase::_840 is a void* in the header (NPCTravel compares it with the address of its own `_1f8`).
    auto* mover = static_cast<Unk_71024f15c0*>(npc->_840);
    if (!mover || !mover->sub_7100EEBB74())
        return 0;
    auto* rail = mover->_8.sub_7100EEB374();
    if (!rail)
        return 0;

    auto* route = static_cast<ksys::map::RailRoute*>(rail);
    sead::SafeString route_id(sead::SafeString::cEmptyString);
    if (route->getRouteId())
        route_id = sead::SafeString(route->getRouteId());
    return route_id == mRoadId;
}

void CheckRoad::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "RoadId");
}

void CheckRoad::loadParams() {
    getDynamicParam(&mRoadId, "RoadId");
}

}  // namespace uking::query
