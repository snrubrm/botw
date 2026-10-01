#include "Game/AI/Action/actionEventSetMoonType.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

EventSetMoonType::EventSetMoonType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetMoonType::~EventSetMoonType() = default;

bool EventSetMoonType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetMoonType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::world::Manager::instance()->getTimeMgr()->setMoonType(
        static_cast<ksys::world::MoonType>(*mMoonType_d));
}

void EventSetMoonType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetMoonType::loadParams_() {
    getDynamicParam(&mMoonType_d, "MoonType");
}

void EventSetMoonType::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
