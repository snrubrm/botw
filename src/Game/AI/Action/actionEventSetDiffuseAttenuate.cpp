#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventSetDiffuseAttenuate.h"

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
    // NON_MATCHING: the original writes the EnvMgr fields without the PtrArray bounds check that
    // getXMgr() keeps (reads like an inline member function of the manager; not repeated elsewhere)
    auto* env = ksys::world::Manager::instance()->getEnvMgr();
    env->_6b5d4 = 2;
    env->mEventDiffuseAttenuateDiameter = *mdiameter_d;
    setFinished();
}

}  // namespace uking::action
