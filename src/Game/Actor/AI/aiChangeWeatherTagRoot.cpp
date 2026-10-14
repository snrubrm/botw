#include "Game/Actor/AI/aiChangeWeatherTagRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

ChangeWeatherTagRoot::ChangeWeatherTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool ChangeWeatherTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChangeWeatherTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(*mTemperatureDay_m, "AddTemperatureDay", -1);
    pack.addFloat(*mTemperatureNight_m, "AddTemperatureNight", -1);
    _98 = false;
    changeChild("通知", &pack);
    mActor->m107();
}

void ChangeWeatherTagRoot::leave_() {
    if (_98) {
        if (auto* bgm = getRemainsElecBattleBgmMaybe()) {
            bgm->_1e8 = false;
            _98 = false;
        }
    }
}

// NON_MATCHING: parameter reloads and temperature-override branches are reordered.
void ChangeWeatherTagRoot::calc_() {
    if (ksys::world::Manager::instance()->mTimer != 0 ||
        ksys::evt::Manager::instance()->hasActiveEvent())
        mActor->m107();
    if (ksys::evt::Manager::instance() && ksys::evt::Manager::instance()->getActiveEvent() &&
        ksys::evt::Manager::instance()->getActiveEvent()->hasFlag(ksys::evt::EventFlowBase::Flag::_80000000000))
        return;
    if (!mActor->checkBasicSig()) {
        if (_98) {
            if (auto* bgm = getRemainsElecBattleBgmMaybe()) {
                bgm->_1e8 = false;
                _98 = false;
            }
        }
        return;
    }
    const s32* weather = nullptr;
    const s32* effect = nullptr;
    const s32* palette = nullptr;
    mActor->m107();
    if (getMapUnitParam(&weather, "Weather") && *weather != -1 && *weather <= 8)
        ksys::world::Manager::instance()->setWeatherType(*weather, true, true, false);
    if (getMapUnitParam(&effect, "WeatherEff") && *effect != -1) {
        if (*effect != 6 ||
            !(ksys::world::Manager::instance()->getEnvMgrUnchecked()->mPaletteSetTransition < 1.0f))
            ksys::world::Manager::instance()->getWeatherMgr()->setWeatherEffect(*effect);
    }
    if (getMapUnitParam(&palette, "PaletteSel") && *palette != -1) {
        const s32 previous = ksys::world::Manager::instance()->getEnvMgr()->getPaletteSet();
        ksys::world::Manager::instance()->getEnvMgr()->setPaletteSet(*palette);
        if (previous != 8 && *palette == 8 && !_98) {
            if (auto* bgm = getRemainsElecBattleBgmMaybe()) {
                bgm->_1e8 = true;
                _98 = true;
            }
        }
    }
    if (mPSelSpeed_m && *mPSelSpeed_m > 0)
        ksys::world::Manager::instance()->getEnvMgr()->setPaletteSelSpeed(*mPSelSpeed_m);
    if (*mTemperatureDay_m < 99999.0f || *mTemperatureNight_m < 99999.0f) {
        auto* manager = ksys::world::Manager::instance();
        manager->mTempDirectDayExtra = *mTemperatureDay_m;
        manager->mTempDirectNightExtra = *mTemperatureNight_m;
        manager->mTempDirectTimer = 4;
    }
    if (*mTemperatureDirectDay_m < 99999.0f)
        ksys::world::Manager::instance()->setTemperatureDay(*mTemperatureDirectDay_m);
    if (*mTemperatureDirectNight_m < 99999.0f)
        ksys::world::Manager::instance()->setTemperatureNight(*mTemperatureDirectNight_m);
    if (*mCloudShadowOff_m)
        ksys::world::Manager::instance()->getSkyMgr()->_3fad = 10;
    if (*mBluffThunderOff_m)
        ksys::world::Manager::instance()->getWeatherMgr()->_36c = 10;
    if (*mIgnitedLevel_m != 0)
        ksys::world::Manager::instance()->setIgnitedLevel(*mIgnitedLevel_m, -1.0f,
                                                         sead::Vector3f(0.0f, 0.0f, 0.0f));
    if (*mFogMinusCorrection_m)
        ksys::world::Manager::instance()->getTempMgr()->x();
}

void ChangeWeatherTagRoot::loadParams_() {
    getMapUnitParam(&mWeather_m, "Weather");
    getMapUnitParam(&mWeatherEff_m, "WeatherEff");
    getMapUnitParam(&mPaletteSel_m, "PaletteSel");
    getMapUnitParam(&mPSelSpeed_m, "PSelSpeed");
    getMapUnitParam(&mIgnitedLevel_m, "IgnitedLevel");
    getMapUnitParam(&mTemperatureDay_m, "TemperatureDay");
    getMapUnitParam(&mTemperatureNight_m, "TemperatureNight");
    getMapUnitParam(&mTemperatureDirectDay_m, "TemperatureDirectDay");
    getMapUnitParam(&mTemperatureDirectNight_m, "TemperatureDirectNight");
    getMapUnitParam(&mCloudShadowOff_m, "CloudShadowOff");
    getMapUnitParam(&mBluffThunderOff_m, "BluffThunderOff");
    getMapUnitParam(&mFogMinusCorrection_m, "FogMinusCorrection");
}

}  // namespace uking::ai
