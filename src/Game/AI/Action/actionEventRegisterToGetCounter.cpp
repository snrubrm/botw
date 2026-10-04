#include "Game/AI/Action/actionEventRegisterToGetCounter.h"

#include "Game/gameEventMgr1.h"

namespace uking::action {

EventRegisterToGetCounter::EventRegisterToGetCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRegisterToGetCounter::~EventRegisterToGetCounter() = default;

bool EventRegisterToGetCounter::oneShot_() {
    EventMgr1::instance()->sub_7100E48ED8(mActorName_d, mGameDataName_d, *mIsInitializeData_d);
    return true;
}

bool EventRegisterToGetCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRegisterToGetCounter::loadParams_() {
    getDynamicParam(&mIsInitializeData_d, "IsInitializeData");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataName_d, "GameDataName");
}

}  // namespace uking::action
