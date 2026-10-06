#include "Game/AI/Query/queryCheckPlayerRideHorse.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

CheckPlayerRideHorse::CheckPlayerRideHorse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerRideHorse::~CheckPlayerRideHorse() = default;

int CheckPlayerRideHorse::doQuery() {
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        if (auto* player = info->getPlayer())
            return player->isRidingHorse();
    }
    return 0;
}

void CheckPlayerRideHorse::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerRideHorse::loadParams() {}

}  // namespace uking::query
