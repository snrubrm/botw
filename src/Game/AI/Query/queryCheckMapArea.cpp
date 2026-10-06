#include "Game/AI/Query/queryCheckMapArea.h"
#include <evfl/Query.h>
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

CheckMapArea::CheckMapArea(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMapArea::~CheckMapArea() = default;

int CheckMapArea::doQuery() {
    if (auto* eco = ksys::eco::Ecosystem::instance()) {
        const char* area_name = &sead::SafeString::cNullChar;
        const s32 area = eco->getFieldMapArea(mActor->getMtx().m[0][3], mActor->getMtx().m[2][3]);
        eco->getAreaNameByNum(area, &area_name);
        return mMapAreaName == sead::SafeString(area_name);
    }
    return 0;
}

void CheckMapArea::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "MapAreaName");
}

void CheckMapArea::loadParams() {
    getDynamicParam(&mMapAreaName, "MapAreaName");
}

}  // namespace uking::query
