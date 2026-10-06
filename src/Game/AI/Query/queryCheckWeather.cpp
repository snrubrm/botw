#include "Game/AI/Query/queryCheckWeather.h"
#include <evfl/Query.h>
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/World/worldManager.h"

namespace uking::query {

CheckWeather::CheckWeather(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWeather::~CheckWeather() = default;

// NON_MATCHING: the original switch is a 7-entry jump table over weather types 2-8 (four distinct case blocks); ours
// has three destination blocks and is lowered to bit tests.
int CheckWeather::doQuery() {
    auto* manager = ksys::world::Manager::instance();
    if (!manager)
        return 0;
    auto* weather = manager->getWeatherMgr();
    if (!weather)
        return 0;
    switch (weather->getWeather()) {
    case ksys::world::WeatherType::Rain:
    case ksys::world::WeatherType::HeavyRain:
    case ksys::world::WeatherType::BlueskyRain:
        return wm::callIsRainingOrSnowingOrThunderStorm(true);
    case ksys::world::WeatherType::Snow:
    case ksys::world::WeatherType::HeavySnow:
        return 2;
    case ksys::world::WeatherType::ThunderStorm:
    case ksys::world::WeatherType::ThunderRain:
        return 3;
    default:
        return 0;
    }
}

void CheckWeather::loadParams(const evfl::QueryArg& arg) {}

void CheckWeather::loadParams() {}

}  // namespace uking::query
