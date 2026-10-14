#include "Game/Actor/Query/queryCheckLastDamageAttacker.h"
#include <evfl/Query.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::query {

CheckLastDamageAttacker::CheckLastDamageAttacker(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckLastDamageAttacker::~CheckLastDamageAttacker() = default;

int CheckLastDamageAttacker::doQuery() {
    auto* player = uking::act::PlayerInfo::instance()->getPlayer();
    if (player)
        return player->_da0 != mName;
    return 1;
}

void CheckLastDamageAttacker::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "Name");
}

void CheckLastDamageAttacker::loadParams() {
    getDynamicParam(&mName, "Name");
}

}  // namespace uking::query
