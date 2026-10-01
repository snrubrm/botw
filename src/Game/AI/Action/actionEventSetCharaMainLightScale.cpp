#include "Game/AI/Action/actionEventSetCharaMainLightScale.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

EventSetCharaMainLightScale::EventSetCharaMainLightScale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetCharaMainLightScale::~EventSetCharaMainLightScale() = default;

bool EventSetCharaMainLightScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCharaMainLightScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCharaMainLightScale::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCharaMainLightScale::loadParams_() {
    getDynamicParam(&mRscale_d, "Rscale");
    getDynamicParam(&mGscale_d, "Gscale");
    getDynamicParam(&mBscale_d, "Bscale");
}

void EventSetCharaMainLightScale::calc_() {
    if (auto* wm = ksys::world::Manager::instance()) {
        sead::Color4f color{*mRscale_d, *mGscale_d, *mBscale_d, 1.0f};
        wm->getEnvMgr()->setCharMainLightScale(color);
        setFinished();
        return;
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
