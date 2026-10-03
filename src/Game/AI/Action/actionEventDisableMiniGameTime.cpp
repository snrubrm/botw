#include "Game/AI/Action/actionEventDisableMiniGameTime.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameEventMgrMiniGame.h"

namespace uking::action {

EventDisableMiniGameTime::EventDisableMiniGameTime(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableMiniGameTime::~EventDisableMiniGameTime() = default;

bool EventDisableMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventDisableMiniGameTime::loadParams_() {}

bool EventDisableMiniGameTime::oneShot_() {
    auto* mini_game = EventMgrMiniGame::instance();
    if (!mini_game)
        return false;
    mini_game->setMode(0);
    ui::minigameScreenHideTimer();
    return true;
}

}  // namespace uking::action
