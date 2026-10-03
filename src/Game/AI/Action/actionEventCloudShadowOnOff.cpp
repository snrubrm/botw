#include "KingSystem/World/worldSkyMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventCloudShadowOnOff.h"

namespace uking::action {

EventCloudShadowOnOff::EventCloudShadowOnOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventCloudShadowOnOff::~EventCloudShadowOnOff() = default;

bool EventCloudShadowOnOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCloudShadowOnOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::world::Manager::instance()->getSkyMgr()->_3f9c = 1;
}

void EventCloudShadowOnOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCloudShadowOnOff::loadParams_() {}

void EventCloudShadowOnOff::calc_() {
    ksys::world::Manager::instance()->getSkyMgr()->_3f9c = 1;
}

}  // namespace uking::action
