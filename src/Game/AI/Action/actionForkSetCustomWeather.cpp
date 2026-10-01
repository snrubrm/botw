#include "Game/AI/Action/actionForkSetCustomWeather.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

ForkSetCustomWeather::ForkSetCustomWeather(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetCustomWeather::~ForkSetCustomWeather() = default;

bool ForkSetCustomWeather::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetCustomWeather::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetCustomWeather::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetCustomWeather::loadParams_() {
    getStaticParam(&mWeatherType_s, "WeatherType");
}

void ForkSetCustomWeather::calc_() {
    if (auto* wm = ksys::world::Manager::instance())
        wm->setWeatherType(*mWeatherType_s, true, true, false);
}

}  // namespace uking::action
