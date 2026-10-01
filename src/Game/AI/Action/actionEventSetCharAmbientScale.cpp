#include "Game/AI/Action/actionEventSetCharAmbientScale.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

EventSetCharAmbientScale::EventSetCharAmbientScale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetCharAmbientScale::~EventSetCharAmbientScale() = default;

bool EventSetCharAmbientScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCharAmbientScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCharAmbientScale::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCharAmbientScale::loadParams_() {
    getDynamicParam(&mRscale_d, "Rscale");
    getDynamicParam(&mGscale_d, "Gscale");
    getDynamicParam(&mBscale_d, "Bscale");
}

void EventSetCharAmbientScale::calc_() {
    if (auto* wm = ksys::world::Manager::instance()) {
        sead::Color4f color{*mRscale_d, *mGscale_d, *mBscale_d, 1.0f};
        wm->getEnvMgr()->setCharAmbientScale(color);
        setFinished();
        return;
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
