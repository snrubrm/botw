#include "Game/AI/Query/queryCheckDeadlyQuestEscapeTiming.h"
#include <evfl/Query.h>
#include "Game/AI/aiUnk_7100736460.h"

namespace uking::query {

CheckDeadlyQuestEscapeTiming::CheckDeadlyQuestEscapeTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckDeadlyQuestEscapeTiming::~CheckDeadlyQuestEscapeTiming() = default;

int CheckDeadlyQuestEscapeTiming::doQuery() {
    return dlc::hasEscapedOneHitObliteratorQuest(true);
}

void CheckDeadlyQuestEscapeTiming::loadParams(const evfl::QueryArg& arg) {}

void CheckDeadlyQuestEscapeTiming::loadParams() {}

}  // namespace uking::query
