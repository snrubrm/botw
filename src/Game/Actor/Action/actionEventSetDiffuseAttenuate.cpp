#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/Actor/Action/actionEventSetDiffuseAttenuate.h"

namespace uking::action {

EventSetDiffuseAttenuate::EventSetDiffuseAttenuate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetDiffuseAttenuate::~EventSetDiffuseAttenuate() = default;

bool EventSetDiffuseAttenuate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDiffuseAttenuate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetDiffuseAttenuate::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetDiffuseAttenuate::loadParams_() {
    getDynamicParam(&mdiameter_d, "diameter");
}

void EventSetDiffuseAttenuate::calc_() {
    auto* env = ksys::world::Manager::instance()->getEnvMgrUnchecked();
    env->mEventDiffuseAttenuateDiameter = *mdiameter_d;
    env->_6b5d4 = 2;
    setFinished();
}

}  // namespace uking::action
