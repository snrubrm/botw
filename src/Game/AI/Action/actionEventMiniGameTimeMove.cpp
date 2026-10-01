#include "Game/AI/Action/actionEventMiniGameTimeMove.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventMiniGameTimeMove::EventMiniGameTimeMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTimeMove::~EventMiniGameTimeMove() = default;

bool EventMiniGameTimeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTimeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::minigameScreenMove();
    setFinished();
}

void EventMiniGameTimeMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameTimeMove::loadParams_() {}

void EventMiniGameTimeMove::calc_() {
    setFinished();
}

}  // namespace uking::action
