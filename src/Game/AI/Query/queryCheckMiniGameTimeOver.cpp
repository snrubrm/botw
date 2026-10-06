#include "Game/AI/Query/queryCheckMiniGameTimeOver.h"
#include <evfl/Query.h>
#include "Game/gameEventMgrMiniGame.h"

namespace uking::query {

CheckMiniGameTimeOver::CheckMiniGameTimeOver(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMiniGameTimeOver::~CheckMiniGameTimeOver() = default;

int CheckMiniGameTimeOver::doQuery() {
    auto* mini_game = EventMgrMiniGame::instance();
    if (mini_game != nullptr)
        return mini_game->getMode() == 2;
    return 0;
}

void CheckMiniGameTimeOver::loadParams(const evfl::QueryArg& arg) {}

void CheckMiniGameTimeOver::loadParams() {}

}  // namespace uking::query
