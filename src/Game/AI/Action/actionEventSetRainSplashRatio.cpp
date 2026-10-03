#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventSetRainSplashRatio.h"

namespace uking::action {

EventSetRainSplashRatio::EventSetRainSplashRatio(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetRainSplashRatio::~EventSetRainSplashRatio() = default;

bool EventSetRainSplashRatio::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetRainSplashRatio::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetRainSplashRatio::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetRainSplashRatio::loadParams_() {
    getDynamicParam(&mRainSplashRatio_d, "RainSplashRatio");
}

void EventSetRainSplashRatio::calc_() {
    // NON_MATCHING: the original writes the WeatherMgr fields without the PtrArray bounds check that
    // getXMgr() keeps (reads like an inline member function of the manager; not repeated elsewhere)
    if (isFailed())
        return;
    if (auto* wm = ksys::world::Manager::instance()) {
        auto* weather = wm->getWeatherMgr();
        weather->_380 = 1;
        weather->_314 = static_cast<int>(*mRainSplashRatio_d);
        setFinished();
        return;
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
