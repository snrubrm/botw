#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

void WeatherMgr::onUnload() {}

void WeatherMgr::rerollClimateWindPowers() {
    auto* wm = Manager::instance();

    f32 power = sead::GlobalRandom::instance()->getF32Range(0.2f, 1.0f);
    if (!wm->getTimeMgr()->isFindDungeonActivated())
        power = sead::GlobalRandom::instance()->getF32Range(0.2f, 0.6666f);

    for (int i = 0; i < int(NumClimates); ++i)
        wm->mWorldInfo.mClimates[i].WindPowerMultiplier = power;
}

bool WeatherMgr::isExposureZero() {
    if (!Manager::instance())
        return false;

    auto* env_mgr = Manager::instance()->getEnvMgr();
    if (!env_mgr)
        return false;

    return env_mgr->getExposure() == 0.0f;
}

WeatherType WeatherMgr::rollNewWeather(Climate climate) {
    auto* wm = Manager::instance();
    int random = sead::GlobalRandom::instance()->getU32(99);
    WeatherType weather = [&] {
        const std::pair<WeatherType, int> rates[] = {
            {WeatherType::Bluesky, wm->getWeatherBlueskyRate(climate) - 1},
            {WeatherType::Cloudy, wm->getWeatherCloudyRate(climate)},
            {WeatherType::Rain, wm->getWeatherRainRate(climate)},
            {WeatherType::HeavyRain, wm->getWeatherHeavyRainRate(climate)},
        };
        for (auto [type, rate] : rates) {
            if (random <= rate)
                return type;
            random -= rate;
        }
        return WeatherType::ThunderRain;
    }();

    if (wm->getEnvMgr()->isWaterRelicRainOn(climate))
        weather = WeatherType::Bluesky;

    bool plateau_done = false;
    auto glider_handle = Manager::instance()->getTimeMgr()->isGetPlayerStole2Flag();
    if (glider_handle != gdt::InvalidHandle) {
        gdt::Manager::instance()->getBool(glider_handle, &plateau_done, true);
    }

    if (plateau_done || weather == WeatherType::Bluesky || weather == WeatherType::Cloudy)
        return weather;
    return WeatherType::Bluesky;
}
}  // namespace ksys::world
