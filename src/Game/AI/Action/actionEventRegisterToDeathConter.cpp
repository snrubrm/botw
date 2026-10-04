#include "Game/AI/Action/actionEventRegisterToDeathConter.h"

#include "Game/gameEventMgr1.h"

namespace uking::action {

EventRegisterToDeathConter::EventRegisterToDeathConter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRegisterToDeathConter::~EventRegisterToDeathConter() = default;

bool EventRegisterToDeathConter::oneShot_() {
    EventMgr1::instance()->sub_7100E48A90(mActorName_d, mGameDataName_d, *mIsInitializeData_d);
    return true;
}

bool EventRegisterToDeathConter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRegisterToDeathConter::loadParams_() {
    getDynamicParam(&mIsInitializeData_d, "IsInitializeData");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataName_d, "GameDataName");
}

}  // namespace uking::action
