#include "Game/AI/Action/actionEventVariableFadeOut.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventVariableFadeOut::EventVariableFadeOut(const InitArg& arg) : EventVariableFade(arg) {}

EventVariableFadeOut::~EventVariableFadeOut() = default;

bool EventVariableFadeOut::init_(sead::Heap* heap) {
    return EventVariableFade::init_(heap);
}

void EventVariableFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    EventVariableFade::enter_(params);
}

void EventVariableFadeOut::leave_() {
    if (*mClipIndex_d >= 0)
        ksys::evt::Manager::instance()->sub_7100DB1158(*mClipIndex_d);
    auto* screen = sub_7100127B30();
    screen->m76();
    screen->open(3);
}

void EventVariableFadeOut::loadParams_() {
    EventVariableFade::loadParams_();
}

void EventVariableFadeOut::calc_() {
    EventVariableFade::calc_();
}

}  // namespace uking::action
