#include "Game/AI/Action/actionEventBgmStartAndKeepAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace uking::action {

EventBgmStartAndKeepAction::EventBgmStartAndKeepAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventBgmStartAndKeepAction::~EventBgmStartAndKeepAction() = default;

bool EventBgmStartAndKeepAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStartAndKeepAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::snd::sub_7100FFD784()->sub_71010078A0(mBgmName_d);
    _30 = false;
}

void EventBgmStartAndKeepAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBgmStartAndKeepAction::loadParams_() {
    getDynamicParam(&mBgmName_d, "BgmName");
}

void EventBgmStartAndKeepAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
