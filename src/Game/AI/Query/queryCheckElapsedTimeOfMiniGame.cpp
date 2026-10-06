#include "Game/AI/Query/queryCheckElapsedTimeOfMiniGame.h"
#include <evfl/Query.h>
#include "Game/gameEventMgrMiniGame.h"

namespace uking::query {

CheckElapsedTimeOfMiniGame::CheckElapsedTimeOfMiniGame(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckElapsedTimeOfMiniGame::~CheckElapsedTimeOfMiniGame() = default;

int CheckElapsedTimeOfMiniGame::doQuery() {
    if (auto* mini_game = EventMgrMiniGame::instance()) {
        const s32 minutes = mini_game->getTimerMs() / 60000;
        const s32 seconds = mini_game->getTimerMs() / 1000 % 60;
        return minutes * 60 + seconds >= *mThreshold;
    }
    return 0;
}

void CheckElapsedTimeOfMiniGame::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckElapsedTimeOfMiniGame::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
