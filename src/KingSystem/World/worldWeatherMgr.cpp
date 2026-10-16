#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>
#include <gfx/seadCamera.h>
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTempMgr.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/World/worldElementWater.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace ksys::world {

// NON_MATCHING: the camera origin x component stays in a register instead of spilling to the stack.
sead::Vector3f sub_71010ED450(f32 distance, f32 angle) {
    const auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return sead::Vector3f::zero;
    const sead::Vector3f origin = camera->getPos();
    sead::Vector3f direction = camera->getAt() - origin;
    const f32 length = direction.length();
    if (length != 0.0f)
        direction *= 1.0f / length;
    else
        direction.set(1.0f, 0.0f, 0.0f);
    direction.normalize();
    if (angle != 0.0f) {
        const f32 yaw = sead::Mathf::atan2(direction.x, direction.z) - angle;
        direction.x = sead::Mathf::sin(yaw);
        direction.z = sead::Mathf::cos(yaw);
    }
    return origin + direction * distance;
}

WeatherMgr::~WeatherMgr() = default;

f32 WeatherMgr::sub_71010ED5B4(const sead::Vector3f& position) {
    sead::Vector3f start = position;
    start.y = 2000.0f;
    sead::Vector3f end = position;
    end.y = -500.0f;
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    act::sub_7100EEACE8(&query);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.setStartAndEnd(start, end);
    if (query.worldRayCast(phys::ContactLayerType::Entity)) {
        sead::Vector3f hit(0.0f, 0.0f, 0.0f);
        query.getHitPosition(&hit);
        return hit.y;
    }
    return 0.0f;
}

WeatherType WeatherMgr::getWeather() const {
    return WeatherType(weather);
}

float WeatherMgr::getTime() const {
    float time = Manager::instance()->getTimeMgr()->getTime();
    if (time >= 60.0f && time < 120.0f)
        return (time - 60.0f) / 60.0f;
    if (time >= 120.0f && time < 180.0f)
        return (time - 120.0f) / 60.0f;
    if (time >= 180.0f && time < 240.0f)
        return (time - 180.0f) / 60.0f;
    if (time >= 240.0f && time < 300.0f)
        return (time - 240.0f) / 60.0f;
    if (time >= 300.0f && time < 360.0f)
        time -= 300.0f;
    return time / 60.0f;
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

// NON_MATCHING: source floats s0/s1 and output integers w8/w9 are swapped.
void WeatherMgr::x_12(const sead::Vector3f& position) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    sead::Vector3f target = position;
    target.y = camera->getPos().y;
    sead::Vector3f direction = camera->getPos() - target;
    const float length = direction.length();
    if (length != 0.0f)
        direction *= 1.0f / length;
    else
        direction.set(1.0f, 0.0f, 0.0f);
    direction.y -= 0.6f;
    _2ac = direction;
}

// NON_MATCHING: source/output registers and request-record copy instructions differ.
void WeatherMgr::x_11(const sead::Vector3f& position) {
    x_12(position);
    ElementLightningCreateArg arg{position, 1};
    sub_71012FDA7C(arg, true);
    sub_71012FDF24(&arg);
    Manager::instance()->getChemicalMgrUnchecked()->m3(&position);
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

bool WeatherMgr::isSnowing() {
    auto* wm = Manager::instance();
    const f32 temp = wm->getTempMgr()->calcTemperature();
    if (temp <= -2.0f || wm->getTempMgr()->_60 <= -2.0f) {
        if (Manager::instance()->getWeatherMgr()->_2dc > 0.1f)
            return true;
    }
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

// 0x710262012c (placeholder name): when set, new water elements get flag 2.
bool sUnk_710262012C;

ElementWater* ElementWater::create(const ElementWaterCreateArg* arg) {
    auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
    if (holder)
        return holder->sub_71010EA040(arg);
    return nullptr;
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
ElementWater::ElementWater(const ElementWaterCreateArg& arg, sead::Heap* heap)
    : Unk_7102518688(ElementName(), heap, false) {
    mArg = arg;
    mArg.actor = nullptr;
    mArg.direction.normalize();
    if (sUnk_710262012C)
        mArg.flags |= 2;
    _1a4 = arg._20;

    ElementName name;
    name.mName = "water";
    if (arg.actor && arg.actor->getChemicalContainer())
        name._18 = arg.actor->getChemicalContainer()->_68;
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

ElementWater::~ElementWater() {
    if (_50) {
        _50->resetLinkedRigidBody();
        delete _50;
        _50 = nullptr;
    }
    if (_58) {
        if (_58->isAddedToWorld())
            _58->removeFromWorldImmediately(nullptr);
        delete _58;
        _58 = nullptr;
    }
    if (_60) {
        ksys::phys::ContactPointInfo::free(_60);
        _60 = nullptr;
    }
    if (!(mArg.flags & 2)) {
        _68.fade();
        _78.fade();
    }
}
