#include "Game/Actor/Query/queryComparePlayerFireResistantLevel.h"
#include <evfl/Query.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::query {

ComparePlayerFireResistantLevel::ComparePlayerFireResistantLevel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

ComparePlayerFireResistantLevel::~ComparePlayerFireResistantLevel() = default;

int ComparePlayerFireResistantLevel::doQuery() {
    if (uking::act::PlayerInfo::instance() && uking::act::PlayerInfo::instance()->getPlayer()) {
        const s32 level = uking::act::PlayerInfo::instance()->getPlayer()->getX();
        return level < 4 ? level : 4;
    }
    return 0;
}

void ComparePlayerFireResistantLevel::loadParams(const evfl::QueryArg& arg) {}

void ComparePlayerFireResistantLevel::loadParams() {}

}  // namespace uking::query
