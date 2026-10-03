#include "Game/AI/Action/actionStopEventMiniGameTime.h"
#include "Game/gameEventMgrMiniGame.h"

namespace uking::action {

StopEventMiniGameTime::StopEventMiniGameTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopEventMiniGameTime::~StopEventMiniGameTime() = default;

bool StopEventMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopEventMiniGameTime::loadParams_() {}

bool StopEventMiniGameTime::oneShot_() {
    EventMgrMiniGame::instance()->setMode(2);
    return true;
}

}  // namespace uking::action
