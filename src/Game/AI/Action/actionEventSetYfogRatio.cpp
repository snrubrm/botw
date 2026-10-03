#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventSetYfogRatio.h"

namespace uking::action {

EventSetYfogRatio::EventSetYfogRatio(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetYfogRatio::~EventSetYfogRatio() = default;

bool EventSetYfogRatio::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetYfogRatio::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetYfogRatio::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetYfogRatio::loadParams_() {
    getDynamicParam(&mYfogRatio_d, "YfogRatio");
}

void EventSetYfogRatio::calc_() {
    // NON_MATCHING: the original writes the EnvMgr fields without the PtrArray bounds check that
    // getXMgr() keeps (reads like an inline member function of the manager; not repeated elsewhere)
    if (isFailed())
        return;
    if (auto* wm = ksys::world::Manager::instance()) {
        auto* env = wm->getEnvMgr();
        env->mEventYfogRatio = *mYfogRatio_d;
        env->_6b5d0 = 2;
        setFinished();
        return;
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
