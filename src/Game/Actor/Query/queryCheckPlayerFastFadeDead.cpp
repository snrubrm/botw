#include "Game/Actor/Query/queryCheckPlayerFastFadeDead.h"
#include <evfl/Query.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::query {

CheckPlayerFastFadeDead::CheckPlayerFastFadeDead(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerFastFadeDead::~CheckPlayerFastFadeDead() = default;

int CheckPlayerFastFadeDead::doQuery() {
    if (auto* info = uking::act::PlayerInfo::instance()) {
        if (auto* player = info->getPlayer())
            return player->_c44.isOnBit(30);
    }
    return 0;
}

void CheckPlayerFastFadeDead::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerFastFadeDead::loadParams() {}

}  // namespace uking::query
