#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTempMgr.h"

namespace ksys::world {

WeatherMgr::~WeatherMgr() = default;

WeatherType WeatherMgr::getWeather() const {
    return WeatherType(weather);
}

u8 WeatherMgr::x_6(int idx) const {
    if (idx <= 5)
        return _284[idx];
    return 0;
}

void WeatherMgr::init_(sead::Heap* heap) {}

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

bool WeatherMgr::x_8() const {
    return _390;
}

// NON_MATCHING: the original reads TempMgr::_60 unconditionally and ORs the two comparisons
// (matches if _60 is read into a local before the ||; see lane4 log, Borderline)
bool WeatherMgr::x_7() {
    auto* wm = Manager::instance();
    const f32 temp = wm->getTempMgr()->calcTemperature();
    return temp <= -2.0f || wm->getTempMgr()->_60 <= -2.0f;
}

void WeatherMgr::setWeatherEffect(int effect) {
    switch (effect) {
    case 0:
        _334 = 4;
        break;
    case 1:
        _338 = 4;
        break;
    case 2:
        _344 = 4;
        break;
    case 3:
        _348 = 4;
        break;
    case 4:
        _34c = 4;
        break;
    case 5:
        _340 = 4;
        break;
    case 6:
        _350 = 4;
        break;
    }
}

void WeatherMgr::calcType2_() {}

void WeatherMgr::x_16() {
    if (_36c != 0)
        --_36c;
    if (_370 != 0)
        --_370;
    if (_374 != 0)
        --_374;
}

void WeatherMgr::x_17() {
    if (_380 != 0)
        --_380;
}

static WeatherType sanitizeWeather(WeatherType weather) {
    if (u8(weather) >= NumWeatherTypes)
        return WeatherType::Bluesky;
    return weather;
}

WeatherType WeatherMgr::x_1(int climate) const {
    return sanitizeWeather(_2a[climate][0]);
}

WeatherType WeatherMgr::x_2(int climate) const {
    return sanitizeWeather(_2a[climate][1]);
}

WeatherType WeatherMgr::x_3(int climate) const {
    return sanitizeWeather(_2a[climate][2]);
}

WeatherType WeatherMgr::x_4(int climate) const {
    return sanitizeWeather(_2a[climate][3]);
}

WeatherType WeatherMgr::x_5(int climate) const {
    return sanitizeWeather(_2a[climate][4]);
}

WeatherType WeatherMgr::x_18(int climate) const {
    return sanitizeWeather(_2a[climate][5]);
}

void WeatherMgr::x_13() {
    _370 = 4;
}

void WeatherMgr::x_14() {
    _374 = 4;
}

void WeatherMgr::sub_71010EDEBC(int value) {
    if (_391 && _320 == 3) {
        _328 = value;
        _324 = value;
    }
}

int WeatherMgr::x() const {
    if (!_391)
        return 0;
    if (_320 != 3)
        return 0;
    return _324;
}

// NON_MATCHING: the original materializes the false result before the first branch and branches
// on the last comparison
bool WeatherMgr::isRaining() {
    auto* wm = Manager::instance();
    const f32 temp = wm->getTempMgr()->calcTemperature();
    if (temp <= -2.0f || wm->getTempMgr()->_60 <= -2.0f)
        return false;
    return Manager::instance()->getWeatherMgr()->_2dc > 0.1f;
}

// NON_MATCHING: same as isRaining
bool WeatherMgr::isSnowing() {
    auto* wm = Manager::instance();
    const f32 temp = wm->getTempMgr()->calcTemperature();
    if (temp <= -2.0f || wm->getTempMgr()->_60 <= -2.0f)
        return Manager::instance()->getWeatherMgr()->_2dc > 0.1f;
    return false;
}

bool isGetPlayerStole2() {
    bool value = false;
    const auto handle = Manager::instance()->getTimeMgr()->isGetPlayerStole2Flag();
    if (handle == gdt::InvalidHandle)
        return false;
    gdt::Manager::instance()->getBool(handle, &value, true);
    return value;
}

}  // namespace ksys::world

namespace wm {

ksys::world::WeatherMgr* getWeatherMgr() {
    const auto* manager = ksys::world::Manager::instance();
    if (!manager)
        return nullptr;
    return manager->getWeatherMgr();
}

}  // namespace wm
