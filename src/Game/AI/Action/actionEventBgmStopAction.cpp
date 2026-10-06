#include "Game/AI/Action/actionEventBgmStopAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace uking::action {

EventBgmStopAction::EventBgmStopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStopAction::~EventBgmStopAction() = default;

bool EventBgmStopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventBgmStopAction::oneShot_() {
    ksys::snd::sub_7100FFD784()->sub_7101007904(*mFadeSec_d, mBgmName_d);
    return true;
}

void EventBgmStopAction::loadParams_() {
    getDynamicParam(&mFadeSec_d, "FadeSec");
    getDynamicParam(&mBgmName_d, "BgmName");
}

}  // namespace uking::action
