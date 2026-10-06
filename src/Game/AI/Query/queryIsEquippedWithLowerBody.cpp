#include "Game/AI/Query/queryIsEquippedWithLowerBody.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

IsEquippedWithLowerBody::IsEquippedWithLowerBody(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquippedWithLowerBody::~IsEquippedWithLowerBody() = default;

int IsEquippedWithLowerBody::doQuery() {
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        auto* player = info->getPlayer();
        if (player && !player->_c44.isOnBit(7))
            return 0;
    }
    return 1;
}

void IsEquippedWithLowerBody::loadParams(const evfl::QueryArg& arg) {}

void IsEquippedWithLowerBody::loadParams() {}

}  // namespace uking::query
