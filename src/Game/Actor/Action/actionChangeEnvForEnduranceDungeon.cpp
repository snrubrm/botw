#include "Game/Actor/Action/actionChangeEnvForEnduranceDungeon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::action {

ChangeEnvForEnduranceDungeon::ChangeEnvForEnduranceDungeon(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ChangeEnvForEnduranceDungeon::~ChangeEnvForEnduranceDungeon() = default;

bool ChangeEnvForEnduranceDungeon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeEnvForEnduranceDungeon::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = true;
    mActor->m107();
}

void ChangeEnvForEnduranceDungeon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeEnvForEnduranceDungeon::loadParams_() {
    getMapUnitParam(&mWeather_m, "Weather");
    getMapUnitParam(&mIgnitedLevel_m, "IgnitedLevel");
    getMapUnitParam(&mWeatherEff_m, "WeatherEff");
    getMapUnitParam(&mPaletteSel_m, "PaletteSel");
    getMapUnitParam(&mTimeForSkyEnv_m, "TimeForSkyEnv");
    getMapUnitParam(&mTemperatureDirectDay_m, "TemperatureDirectDay");
    getMapUnitParam(&mTemperatureDirectNight_m, "TemperatureDirectNight");
}

void ChangeEnvForEnduranceDungeon::calc_() {
    if (!mActor->checkBasicSig()) {
        _1c = true;
        return;
    }

    mActor->m107();
    if (*mWeather_m != -1) {
        if (_1c)
            ksys::world::Manager::instance()->setWeatherType(*mWeather_m, false, false, false);
        else
            ksys::world::Manager::instance()->setWeatherType(*mWeather_m, true, false, false);
        _1c = false;
    }
    if (*mTimeForSkyEnv_m != -1) {
        ksys::world::Manager::instance()->getTimeMgr()->setAocFieldTimeForSkyEnv(
            static_cast<f32>(*mTimeForSkyEnv_m) * 15.0f);
    }

    const s32* effect = nullptr;
    const s32* palette = nullptr;
    if (getMapUnitParam(&effect, "WeatherEff") && *effect != -1) {
        if (*effect != 6 ||
            !(ksys::world::Manager::instance()->getEnvMgrUnchecked()->getPaletteSetTransition() < 1.0f))
            ksys::world::Manager::instance()->getWeatherMgr()->setWeatherEffect(*effect);
    }
    if (getMapUnitParam(&palette, "PaletteSel") && *palette != -1) {
        ksys::world::Manager::instance()->getEnvMgr()->getPaletteSet();
        ksys::world::Manager::instance()->getEnvMgr()->setPaletteSet(*palette);
    }
    ksys::world::Manager::instance()->getEnvMgr()->setPaletteSelSpeed(2);

    if (*mTemperatureDirectDay_m < 99999.0f)
        ksys::world::Manager::instance()->setTemperatureDay(*mTemperatureDirectDay_m);
    if (*mTemperatureDirectNight_m < 99999.0f)
        ksys::world::Manager::instance()->setTemperatureNight(*mTemperatureDirectNight_m);

    if (*mIgnitedLevel_m != 0) {
        u32 hash_id = 0;
        if (mActor->getMapObjIter().tryGetParamUIntByKey(&hash_id, "HashId") && hash_id == 0x457b9f31) {
            ksys::world::Manager::instance()->setIgnitedLevel(*mIgnitedLevel_m, 125.0f,
                                                             {-3350.0f, 300.0f, -2450.0f});
        } else {
            ksys::world::Manager::instance()->setIgnitedLevel(*mIgnitedLevel_m, -1.0f,
                                                             {0.0f, 0.0f, 0.0f});
        }
    }
}

}  // namespace uking::action
