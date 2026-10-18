#include "KingSystem/Effect/eftRainbow.h"
#include <gfx/seadCamera.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::eft {

void Rainbow::start() {
    mEnabled = true;
    mDelay = 0.0f;
    mTimeLeft = 0.0f;
}

void Rainbow::stop() {
    mEnabled = false;
}

// NON_MATCHING: weather gates and timer/color operations are scheduled differently.
void Rainbow::calc() {
    if (!mEnabled)
        return;
    auto* world = world::Manager::instance();
    const f32 time = world->getTimeMgrUnchecked()->getTime();
    const auto weather = world->getWeatherMgr()->getWeather();
    const bool clear = weather == world::WeatherType::Bluesky ||
                       weather == world::WeatherType::BlueskyRain;
    const bool blocked = !clear || (Effect::instance()->_192b4 == 0.0f && !(mFlags & 1));
    const auto* weather_mgr = world->getWeatherMgrUnchecked();
    const bool environment_clear =
        weather_mgr->_2e4 == 0.0f && weather_mgr->_2e8 == 0.0f &&
        weather_mgr->_2f0 == 0.0f && weather_mgr->_2f4 == 0.0f &&
        weather_mgr->_2f8 == 0.0f && weather_mgr->_2ec == 0.0f &&
        weather_mgr->_2fc == 0.0f && world->getEnvMgr()->getConcentrationBM() == 0.0f;
    const bool palette_clear = environment_clear &&
        u32(world->getEnvMgrUnchecked()->mPaletteSetOverride) + 1 < 2;
    if (!blocked && ((time > 90.0f && time < 135.0f) ||
                     (time > 240.0f && time < 270.0f)) && palette_clear && mTimeLeft <= 0.0f) {
        mDelay = mDelayDuration;
        mTimeLeft = mDuration;
        const f32 random = sead::GlobalRandom::instance()->getF32();
        mRandomFactor = random * random;
    }
    const f32 delta = VFR::instance()->getDeltaFrame();
    if (mDelay > 0.0f) {
        mDelay -= delta * (1.0f / 30.0f);
        if (mDelay < 0.0f)
            mDelay = 0.0f;
        return;
    }
    if (mTimeLeft <= 0.0f) {
        mRainbow.fade();
        mMirror.fade();
        return;
    }
    mTimeLeft = sead::Mathf::max(mTimeLeft - delta * (1.0f / 30.0f), 0.0f);
    const auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    sead::Vector3f direction = mDirection;
    direction.normalize();
    mAlpha = 1.0f;
    if (mTimeLeft > mDuration - mFadeTime)
        mAlpha = 1.0f - (mTimeLeft - (mDuration - mFadeTime)) / mFadeTime;
    if (mTimeLeft < mFadeTime)
        mAlpha = mTimeLeft / mFadeTime;
    mAlpha = sead::Mathf::clamp(mAlpha, 0.0f, 1.0f);
    const auto position = camera->getPos() + direction * mDistance;
    const f32 scale = mScaleMin * (1.0f - mRandomFactor) + mRandomFactor * mScaleMax;
    const f32 power = mAlpha * ((1.0f - mRandomFactor) * mPowerMin + mRandomFactor * mPowerMax);
    if (!mRainbow.isActive() && act::Reaction::instance()->_28)
        mRainbow = searchAndEmitELink(act::Reaction::instance()->_28, "Rainbow");
    mRainbow.setPosition(position, scale);
    mRainbow.setDelayEmitParamColor(sead::Color4f(power, power, power, 1.0f));
    if ((mRandomFactor - 0.7f) * mMirrorPower * power > 0.0f && !(mFlags & 2)) {
        if (!mMirror.isActive() && act::Reaction::instance()->_28)
            mMirror = searchAndEmitELink(act::Reaction::instance()->_28, "Rainbow_Mirror");
        mMirror.setPosition(position, scale * mMirrorScale);
        const f32 mirror_power = power * mMirrorPower;
        mMirror.setDelayEmitParamColor(sead::Color4f(mirror_power, mirror_power, mirror_power, 1.0f));
    } else {
        mMirror.fade();
    }
    if (!clear || !palette_clear)
        mTimeLeft = 0.0f;
}

}  // namespace ksys::eft
