#include "Game/Actor/Query/queryIsEquippedEnableDye.h"
#include <evfl/Query.h>
#include "Game/Actor/Player/actPlayerBase.h"

namespace uking::query {

IsEquippedEnableDye::IsEquippedEnableDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquippedEnableDye::~IsEquippedEnableDye() = default;

int IsEquippedEnableDye::doQuery() {
    s32 dye;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        dye = accessor.getArmorDyeStuff();
    }
    if (dye != 0)
        return dye != 3;
    return 2;
}

void IsEquippedEnableDye::loadParams(const evfl::QueryArg& arg) {}

void IsEquippedEnableDye::loadParams() {}

}  // namespace uking::query
