#include "Game/AI/Query/queryCheckCurrentMap.h"
#include <evfl/Query.h>
#include "KingSystem/System/StageInfo.h"

namespace uking::query {

CheckCurrentMap::CheckCurrentMap(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckCurrentMap::~CheckCurrentMap() = default;

int CheckCurrentMap::doQuery() {
    return ksys::StageInfo::getCurrentMapName() == mMapName;
}

void CheckCurrentMap::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "MapName");
}

void CheckCurrentMap::loadParams() {
    getDynamicParam(&mMapName, "MapName");
}

}  // namespace uking::query
