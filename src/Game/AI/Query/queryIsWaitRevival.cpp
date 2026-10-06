#include "Game/AI/Query/queryIsWaitRevival.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

IsWaitRevival::IsWaitRevival(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsWaitRevival::~IsWaitRevival() = default;

int IsWaitRevival::doQuery() {
    return mActor->isWaitRevivalForUsed();
}

void IsWaitRevival::loadParams(const evfl::QueryArg& arg) {}

void IsWaitRevival::loadParams() {}

}  // namespace uking::query
