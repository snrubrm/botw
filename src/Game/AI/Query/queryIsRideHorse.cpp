#include "Game/AI/Query/queryIsRideHorse.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actHorseRideInfo.h"

namespace uking::query {

IsRideHorse::IsRideHorse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsRideHorse::~IsRideHorse() = default;

// NON_MATCHING: same logic; ours branches the second null check straight to the epilogue (x0 is already
// null) while the original jumps to a separate `mov w0, wzr`.
int IsRideHorse::doQuery() {
    auto* actor = mActor;
    if (actor && actor->getPlayerRideInfo())
        return actor->getPlayerRideInfo()->_30 & 1;
    return 0;
}

void IsRideHorse::loadParams(const evfl::QueryArg& arg) {}

void IsRideHorse::loadParams() {}

}  // namespace uking::query
