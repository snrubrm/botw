#include "Game/Actor/Query/queryCheckPlayerRideHorse.h"
#include <evfl/Query.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::query {

CheckPlayerRideHorse::CheckPlayerRideHorse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerRideHorse::~CheckPlayerRideHorse() = default;

int CheckPlayerRideHorse::doQuery() {
    if (auto* info = uking::act::PlayerInfo::instance()) {
        if (auto* player = info->getPlayer())
            return player->isRidingHorse();
    }
    return 0;
}

void CheckPlayerRideHorse::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerRideHorse::loadParams() {}

}  // namespace uking::query
