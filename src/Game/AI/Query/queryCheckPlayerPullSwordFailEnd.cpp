#include "Game/AI/Query/queryCheckPlayerPullSwordFailEnd.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

CheckPlayerPullSwordFailEnd::CheckPlayerPullSwordFailEnd(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckPlayerPullSwordFailEnd::~CheckPlayerPullSwordFailEnd() = default;

int CheckPlayerPullSwordFailEnd::doQuery() {
    s32 result;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (!accessor.hasProc())
            result = 0;
        else
            result = !accessor.x_39();
    }
    return result;
}

void CheckPlayerPullSwordFailEnd::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerPullSwordFailEnd::loadParams() {}

}  // namespace uking::query
