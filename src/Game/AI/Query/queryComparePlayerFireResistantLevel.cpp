#include "Game/AI/Query/queryComparePlayerFireResistantLevel.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

ComparePlayerFireResistantLevel::ComparePlayerFireResistantLevel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

ComparePlayerFireResistantLevel::~ComparePlayerFireResistantLevel() = default;

int ComparePlayerFireResistantLevel::doQuery() {
    if (ksys::act::PlayerInfo::instance() && ksys::act::PlayerInfo::instance()->getPlayer()) {
        const s32 level = ksys::act::PlayerInfo::instance()->getPlayer()->getX();
        return level < 4 ? level : 4;
    }
    return 0;
}

void ComparePlayerFireResistantLevel::loadParams(const evfl::QueryArg& arg) {}

void ComparePlayerFireResistantLevel::loadParams() {}

}  // namespace uking::query
