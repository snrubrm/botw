#include "Game/AI/Query/queryCheckPlayerDeadCause.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

CheckPlayerDeadCause::CheckPlayerDeadCause(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerDeadCause::~CheckPlayerDeadCause() = default;

// NON_MATCHING: same logic; the original computes the table / kind selects first and only then tests cause 12 / 10
// (ours tests them before the selects), and its index is `(s16)(cause - 1)` after the range check.
int CheckPlayerDeadCause::doQuery() {
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return 0;

    const u32 reason = player->getDeathReason();
    const u16 cause = reason;
    const u32 kind = reason >> 16;

    int result;
    switch (static_cast<u16>(cause - 1)) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
        result = 4;
        break;
    case 5:
        result = 5;
        break;
    case 6:
        result = 6;
        break;
    case 7:
        result = 7;
        break;
    case 8:
        result = 8;
        break;
    case 9:
        result = 0;
        break;
    case 10:
        result = 13;
        break;
    default:
        result = 0;
        break;
    }
    if (kind == 2)
        result = cause == 7 ? 6 : 9;
    if (kind == 4)
        result = 10;
    if (cause == 12)
        return 12;
    if (cause == 10)
        return 11;
    return result;
}

void CheckPlayerDeadCause::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerDeadCause::loadParams() {}

}  // namespace uking::query
