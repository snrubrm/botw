#include "Game/AI/Query/queryCheckPlayerHellType.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

CheckPlayerHellType::CheckPlayerHellType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerHellType::~CheckPlayerHellType() = default;

int CheckPlayerHellType::doQuery() {
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
    if (player)
        return *mPlayerHellType == player->_d18;
    return 0;
}

void CheckPlayerHellType::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "PlayerHellType");
}

void CheckPlayerHellType::loadParams() {
    getDynamicParam(&mPlayerHellType, "PlayerHellType");
}

}  // namespace uking::query
