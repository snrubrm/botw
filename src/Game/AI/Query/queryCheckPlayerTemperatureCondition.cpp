#include "Game/AI/Query/queryCheckPlayerTemperatureCondition.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

// 0x71006deb48: DynamicActor::m151 of the accessor's actor (src/Game/Damage/dmgActorAccessors.cpp).
bool sub_71006DEB48(const ksys::act::ActorConstDataAccess& accessor, int bit);

namespace uking::query {

CheckPlayerTemperatureCondition::CheckPlayerTemperatureCondition(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckPlayerTemperatureCondition::~CheckPlayerTemperatureCondition() = default;

int CheckPlayerTemperatureCondition::doQuery() {
    int result;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (player.hasProc())
            result = sub_71006DEB48(player, 0) ? 0 : 1 + sub_71006DEB48(player, 1);
        else
            result = 1;
    }
    return result;
}

void CheckPlayerTemperatureCondition::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerTemperatureCondition::loadParams() {}

}  // namespace uking::query
