#include "KingSystem/World/worldTempMgr.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::world {

// NON_MATCHING: reset() is inlined - same store merging difference as in reset()
TempMgr::TempMgr() {
    reset();
}

// NON_MATCHING: the original merges the constant stores differently (0x60 and 0x80 as 64-bit stores)
void TempMgr::reset() {
    _20 = 23.0;
    _24.value = 23.0;
    _24.prev_value = 23.0;
    _30 = 0.0;
    _34 = 0.0;
    _38 = 0.0;
    _3c = 23.0;
    _40 = 23.0;
    _44 = 23.0;
    _54 = 0.4;
    _58 = 50.0;
    _5c = -50.0;
    _60 = 0.0;
    _64 = 0;
    _68 = -1;
    _6c = -1;
    _70 = 0.0;
    _74 = 0.0;
    _78 = 0.0;
    _7c = 0;
    _80 = 0.2;
    _84 = 1.0;
    _88 = 1.0;
}

// `{ ; }` like upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229): the original stores the vtable
// pointers (two bases) before tail calling ~Job, which a defaulted destructor drops.
TempMgr::~TempMgr() {
    ;
}

void TempMgr::init_(sead::Heap* heap) {}

static f32 getWeatherTemperatureOffset(s8 weather) {
    switch (weather) {
    case s8(WeatherType::Bluesky):
        return 0.0;
    case s8(WeatherType::Cloudy):
        return -1.5;
    case s8(WeatherType::Rain):
    case s8(WeatherType::HeavyRain):
    case s8(WeatherType::Snow):
    case s8(WeatherType::HeavySnow):
        return -3.0;
    case s8(WeatherType::ThunderStorm):
        return -1.5;
    default:
        return -3.0;
    }
}

// NON_MATCHING: regalloc (x8/x10) and one fadd/str reordered
f32 TempMgr::calcTemperature() {
    const f32 height = Manager::instance()->mPlayerPos.y;
    _34 = height;
    const f32 temp_day = Manager::instance()->calcTempDay(height);
    const f32 temp_night = Manager::instance()->calcTempNight(_34);
    const f32 t = Manager::instance()->getTimeMgr()->getTemperatureMultiplier();
    f32 temp = temp_day + (temp_night - temp_day) * t;

    if (Manager::instance()->auto7()) {
        _30 = 0.0;
    } else {
        const auto weather = Manager::instance()->getWeatherMgr()->getWeather();
        const auto* weather_mgr = Manager::instance()->getWeatherMgr();
        const f32 blend = weather_mgr->_24;
        const s8 prev_weather = weather_mgr->_29;
        const f32 offset = getWeatherTemperatureOffset(s8(weather));
        const f32 prev_offset = getWeatherTemperatureOffset(prev_weather);
        _30 = blend * offset + (1.0f - blend) * prev_offset;
        temp += _30;
    }
    return temp;
}

f32 TempMgr::sub_71010E58C0() {
    const f32 r = sead::GlobalRandom::instance()->getF32();
    const int hour = Manager::instance()->getTimeMgr()->getHour();
    f32 t = r;
    if (Manager::instance()->getFogType() != 1 && hour >= 5 && hour < 10)
        t = r * 0.5f + 0.5f;
    const f32 max = Manager::instance()->getMoistureMax();
    const f32 min = Manager::instance()->getMoistureMin();
    return min + t * (max - min);
}

f32 TempMgr::sub_71010E5F00() const {
    f32 rate = _54;
    if (_64 != 0 || Manager::instance()->mTimer != 0)
        rate = 100.0;
    return rate;
}

// NON_MATCHING: regalloc (s1/s2 swapped) and fadd operand order
// NON_MATCHING: the "no fog" path re-stores the moisture target (tail-merged store)
void TempMgr::calc2() {
    auto* wm = Manager::instance();
    const int hour = wm->getTimeMgr()->getHour();
    const int climate = int(wm->getCurrentClimate());

    if (_6c != climate) {
        _70 = sub_71010E58C0();
        _6c = climate;
    }

    if (_68 != hour) {
        _70 = sub_71010E58C0();
        _68 = hour;
    }

    const auto weather = wm->getWeatherMgr()->getWeather();
    const f32 base = _70;
    f32 bloom_threshold = 1.0;
    f32 bloom_intensity = 1.0;
    f32 value;
    bool influenced;

    if (wm->getWeatherMgr()->_24 >= 0.9f) {
        f32 add;
        switch (weather) {
        case WeatherType::Cloudy:
        case WeatherType::ThunderStorm:
            add = wm->getEnvMgr()->mWeatherInfluences[0].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[0].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[0].BloomIntencity.ref();
            _74 = 0.5;
            break;
        case WeatherType::Rain:
            add = wm->getEnvMgr()->mWeatherInfluences[2].AddMoisture.ref();
            _74 = 15.0;
            _78 = wm->getEnvMgr()->mWeatherInfluences[2].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[2].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[2].BloomIntencity.ref();
            break;
        case WeatherType::Snow:
            add = wm->getEnvMgr()->mWeatherInfluences[2].AddMoisture.ref();
            _74 = 0.5;
            _78 = wm->getEnvMgr()->mWeatherInfluences[2].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[2].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[2].BloomIntencity.ref();
            break;
        case WeatherType::HeavyRain:
        case WeatherType::ThunderRain:
            add = wm->getEnvMgr()->mWeatherInfluences[3].AddMoisture.ref();
            _74 = 15.0;
            _78 = wm->getEnvMgr()->mWeatherInfluences[3].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[3].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[3].BloomIntencity.ref();
            break;
        case WeatherType::HeavySnow:
            add = wm->getEnvMgr()->mWeatherInfluences[3].AddMoisture.ref();
            _74 = 0.5;
            _78 = wm->getEnvMgr()->mWeatherInfluences[3].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[3].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[3].BloomIntencity.ref();
            break;
        case WeatherType::BlueskyRain:
            add = wm->getEnvMgr()->mWeatherInfluences[1].AddMoisture.ref();
            _74 = 15.0;
            _78 = wm->getEnvMgr()->mWeatherInfluences[1].AddMoisture.ref();
            bloom_threshold = wm->getEnvMgr()->mWeatherInfluences[1].BloomThreshhold.ref();
            bloom_intensity = wm->getEnvMgr()->mWeatherInfluences[1].BloomIntencity.ref();
            break;
        default:
            goto not_influenced;
        }

        value = base + add;
        if (value > 100.0f)
            value = 100.0f;
        influenced = true;
    } else {
    not_influenced:
        value = base;
        if (value > 100.0f)
            value = 100.0f;
        if (_74 > 0.0f)
            value += _78;

        if (wm->getTimeMgr()->isTimeFlowingNormally()) {
            _74 -= wm->getTimeMgr()->getTimeStep() * VFR::instance()->getDeltaFrame();
            _74 = sead::Mathf::max(0.0f, _74);
        }
        influenced = false;
    }

    bool timer_active = false;
    if (_7c != 0) {
        --_7c;
        timer_active = true;
    }

    f32 target = value;
    if (wm->getFogType() != 0) {
        f32 wind = wm->getWindSpeed() / 10.0f;
        if (wind > 1.0f)
            wind = 1.0f;
        target = wind * 60.0f;
        if (_74 > 0.0f)
            target += _78;
    }

    f32 max_delta;
    if (!wm->getTimeMgr()->isFindDungeonActivated()) {
        target = 7.5;
        max_delta = 0.1;
    } else if (timer_active && target > 20.0f) {
        target = 20.0;
        max_delta = 0.5;
    } else {
        max_delta = 0.1;
    }
    VFR::lerp(&_38, target, 0.1f, max_delta, 0.01f);

    if (_74 <= 0.0f || influenced) {
        VFR::lerp(&_84, bloom_threshold, 0.01f, 0.01f, 0.005f);
        VFR::lerp(&_88, bloom_intensity, 0.01f, 0.01f, 0.005f);
    }
}

void TempMgr::calc1() {
    const f32 temp = calcTemperature();
    _24.chase(temp, sub_71010E5F00());
    _24.updateStats();
    _20 = _24.value;

    _60 = 0.0;
    f32 offset = 0.0;
    switch (Manager::instance()->_798) {
    case 1:
        offset = _58;
        _60 = 49.9;
        offset = _20 + offset <= 49.9f ? offset : _20 < 49.9f ? 49.9f - _20 : 0.0f;
        break;
    case 2:
        offset = _5c;
        _60 = -9.9;
        offset = _20 + offset >= -9.9f ? offset : _20 > -9.9f ? -9.9f - _20 : 0.0f;
        break;
    }

    _40 = _44;
    _20 += offset;
    _3c = _20;
}

void TempMgr::calc_() {
    if (Manager::instance()->mWorldInfoLoadStatus == Manager::WorldInfoLoadStatus::Loaded) {
        calc1();
        calc2();
    }

    if (Manager::instance()->hasCameraOrPlayerMoved(20.0))
        _64 = 10;

    if (_64 != 0)
        --_64;
}

void TempMgr::setInstantTemperature() {
    _64 = 8;
}

void TempMgr::x() {
    _7c = 2;
    _80 = 0.2;
}

void TempMgr::calcType2_() {}

}  // namespace ksys::world
