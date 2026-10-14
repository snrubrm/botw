#include "KingSystem/Sound/Actor/Action/actionEventBgmStartAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

EventBgmStartAction::EventBgmStartAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmStartAction::~EventBgmStartAction() = default;

bool EventBgmStartAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventBgmStartAction::oneShot_() {
    ksys::snd::sub_7100FFD784()->sub_71010078A0(mBgmName_d);
    return true;
}

void EventBgmStartAction::loadParams_() {
    getDynamicParam(&mBgmName_d, "BgmName");
}

}  // namespace ksys::snd
