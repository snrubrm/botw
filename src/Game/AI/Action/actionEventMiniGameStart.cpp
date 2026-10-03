#include "Game/AI/Action/actionEventMiniGameStart.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventMiniGameStart::EventMiniGameStart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameStart::~EventMiniGameStart() = default;

bool EventMiniGameStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameStart::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A992CC(*mTextType_d);
}

void EventMiniGameStart::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameStart::loadParams_() {
    getDynamicParam(&mTextType_d, "TextType");
}

void EventMiniGameStart::calc_() {
    if (ui::sub_7100A993BC()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
