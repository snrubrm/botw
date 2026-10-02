#include "Game/AI/Action/actionEventSetAddFogOff.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTempMgr.h"

namespace uking::action {

EventSetAddFogOff::EventSetAddFogOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetAddFogOff::~EventSetAddFogOff() = default;

bool EventSetAddFogOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetAddFogOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetAddFogOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetAddFogOff::loadParams_() {}

void EventSetAddFogOff::calc_() {
    if (isFailed())
        return;
    ksys::world::Manager::instance()->getTempMgr()->x();
    setFinished();
}

}  // namespace uking::action
