#include "Game/AI/Query/queryIsPlayerGrounded.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

IsPlayerGrounded::IsPlayerGrounded(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsPlayerGrounded::~IsPlayerGrounded() = default;

int IsPlayerGrounded::doQuery() {
    bool grounded;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        grounded = accessor.isBgCrossFoot();
    }
    if (!grounded)
        return 0;
    bool sliding;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        sliding = accessor.isBgCrossSlideFoot();
    }
    if (sliding)
        return 0;
    bool grounded_check;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        grounded_check = accessor.groundedCheckStuff();
    }
    return !grounded_check;
}

void IsPlayerGrounded::loadParams(const evfl::QueryArg& arg) {}

void IsPlayerGrounded::loadParams() {}

}  // namespace uking::query
