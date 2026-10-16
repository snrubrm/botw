#include <cmath>
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Sound/sndSound.h"
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
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"

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

// NON_MATCHING: the original passes `this` to every rollNewWeather call; ours does not because our
// rollNewWeather never reads it (clang passes undef for an unused argument of a function in the same TU).
void WeatherMgr::calcNewWeathers() {
    if (Manager::instance()->getStageType() == StageType::OpenWorldTest)
        return;

    for (int i = 0; i < int(NumClimates); ++i) {
        auto& weathers = _2a[i];
        for (int j = 0; j < 12; ++j)
            weathers[j] = weathers[j + 6];
        for (int j = 12; j < 18; ++j)
            weathers[j] = rollNewWeather(Climate(i));
    }
    x_0();
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

// NON_MATCHING: the original stores the event scale (1, 1, 1) as one 8-byte store at 0xb4 and a 4-byte one at 0xbc.
void WeatherMgr::x_10() {
    const sead::Vector3f pos =
        sub_71010ED450(2000.0f, sead::GlobalRandom::instance()->getF32Range(-0.65f, 0.65f));
    auto* actor = act::Reaction::instance()->_38;
    if (!actor)
        return;
    const f32 y = Manager::instance()->getCameraPos().y;
    Unk_71012419b4 handle;
    xlinkSearchAndEmit(actor, "Far_Lightning", 2, &handle);
    handle.mELink.setPosition({pos.x, y, pos.z});
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

// 0x7102620128 (placeholder name): when set, fixing a water element also kills its effects (m33).
KSYS_VISIBILITY_HIDDEN bool sUnk_7102620128;
// 0x710262012c (placeholder name): when set, new water elements get flag 2.
KSYS_VISIBILITY_HIDDEN bool sUnk_710262012C;

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

// 0x710250d120: three floats in .data; m29 copies the first to _1ac, m35 0x71010e9368 grows _1ac from the
// first to the second over the third (frames).
// Nothing writes them, so they are non-static and hidden to keep the load.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710250D120[3] = {0.5f, 2.5f, 50.0f};

// NON_MATCHING: scheduling and regalloc (1832 bytes against 1800).
void ElementWater::m35(f32 delta_frame) {
    if (mHolder->_64.length() > 0.0f)
        _58->applyLinearImpulse(mHolder->_64);

    f32 radius = mArg._20;
    if (_1a0 & 1)
        radius -= _1a8;

    auto* core = sead::DynamicCast<ksys::phys::SphereRigidBody>(_58);
    if (!core)
        return;
    auto* sensor = sead::DynamicCast<ksys::phys::SphereRigidBody>(_50);
    if (!sensor)
        return;

    sead::Vector3f direction = core->getLinearVelocity();
    const f32 speed = direction.normalize();
    const sead::Vector3f position = core->getPosition();
    mArg._20 = radius;
    mArg._24 = speed;
    mArg.direction = direction;
    mArg.position = position;
    mHolder->_3c = speed;
    mHolder->_1c = direction;
    if (radius > 0.1f)
        sensor->setRadius(radius);
    else
        x();

    if (!(mArg.flags & 4)) {
        if (auto* sound = ksys::snd::SoundMgr::instance()) {
            if (sound->_38) {
                if (auto* mgr = sound->_38->sub_710102C10C())
                    mgr->sub_7101039588(mArg._20, mArg.position);
            }
        }
    }

    if (_60->getNumContactPoints() != 0 && !_60->begin().isEnd()) {
        for (auto it = _60->begin(), end = _60->end(); it != end; ++it) {
            const auto layer = it.getPoint()->body_b->getContactLayer();
            switch (layer) {
            case ksys::phys::ContactLayer::EntityGroundObject:
            case ksys::phys::ContactLayer::EntityGround:
            case ksys::phys::ContactLayer::EntityGroundSmooth:
            case ksys::phys::ContactLayer::EntityGroundRough:
                _68.fade();
                x();
                break;
            case ksys::phys::ContactLayer::EntityWater:
                x();
                break;
            default:
                break;
            }
        }
        _1a0 |= 1;
        sub_71010E9A70();
    }

    if (_68.isActive()) {
        if (!(mArg.flags & 8)) {
            _1ac += (sUnk_710250D120[1] - sUnk_710250D120[0]) * delta_frame / sUnk_710250D120[2];
            if (_1ac > sUnk_710250D120[1])
                _1ac = sUnk_710250D120[1];
        } else {
            _1ac += delta_frame * 0.95f / 60.0f;
            if (_1ac > 1.75f)
                _1ac = 1.75f;
        }

        const sead::Vector3f& dir = mArg.direction;
        const sead::Vector3f& up = sead::Mathf::abs(dir.dot(sead::Vector3f::ey)) > 0.999f ?
                                       sead::Vector3f::ex :
                                       sead::Vector3f::ey;
        sead::Vector3f x_axis;
        x_axis.setCross(up, dir);
        x_axis.normalize();
        sead::Vector3f y_axis;
        y_axis.setCross(dir, x_axis);
        y_axis.normalize();
        const f32 scale = mArg._20 * _1ac;
        sead::Matrix34f mtx;
        mtx.setBase(0, x_axis);
        mtx.setBase(1, y_axis);
        mtx.setBase(2, dir);
        mtx.setTranslation(mArg.position);
        _68.setMatrix(mtx, {scale, scale, scale});
    }

    if (mHolder->_58 & 2) {
        sub_71010E9A70();
        x();
        _68.fade();
    }
}

// NON_MATCHING: the effect name is picked with selects (the original branches).
void ElementWater::sub_71010E9A70() {
    if (!(mArg.flags & 2) && !_78.isActive()) {
        const char* effect;
        if (mArg.flags & 8)
            effect = "Chemical_Splash_Ibutsu";
        else if (mArg.flags & 0x10)
            effect = "Chemical_Splash_Ibutsu_2";
        else if (mArg.flags & 0x20)
            effect = "Chemical_Splash_Ibutsu_3";
        else
            effect = "Chemical_Splash";
        _78 = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_38, effect);
        if (_78.isActive()) {
            const sead::Vector3f& dir = mArg.direction;
            const sead::Vector3f& up =
                sead::Mathf::abs(dir.dot(sead::Vector3f::ey)) > 0.999f ? sead::Vector3f::ex :
                                                                         sead::Vector3f::ey;
            sead::Vector3f x;
            x.setCross(up, dir);
            x.normalize();
            sead::Vector3f y;
            y.setCross(dir, x);
            y.normalize();
            sead::Matrix34f mtx;
            mtx.setBase(0, x);
            mtx.setBase(1, y);
            mtx.setBase(2, dir);
            mtx.setTranslation(mArg.position);
            _78.setMatrix(mtx);
        }
    }

    if (!(mArg.flags & 4)) {
        if (auto* sound = ksys::snd::SoundMgr::instance()) {
            if (sound->_38) {
                if (auto* mgr = sound->_38->sub_710102C10C())
                    mgr->sub_7101039920(mArg._20, mArg.position);
            }
        }
    }
}

// NON_MATCHING: the original builds both SphereParams in one stack slot and stores the mass clamp
// conditionally (ours: fmin); 1664 bytes against 1752.
bool ElementWater::m29(const ElementName& name, sead::Heap* heap) {
    sead::Matrix34f mtx;
    mtx.makeT(mArg.position);

    {
        ksys::phys::SphereParam param;
        param.name = "WaterChemicalSensor";
        param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
        param.radius = mArg._20;
        param.motion_type = ksys::phys::MotionType::Keyframed;
        _50 = ksys::phys::SphereRigidBody::make(&param, heap);
    }
    if (!_50)
        return false;
    _50->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    setRigidBody(_50, true);

    const f32 half = mArg._20 * 0.5f;
    mHolder->_38 = half * half * sead::Mathf::pi();
    mHolder->_3c = mArg._24;
    mHolder->_1c = mArg.direction;
    mHolder->_30 = (mArg.flags & 1) ? ksys::world::Manager::instance()->getTempMgr()->get_3c() :
                                      mArg._28;

    _60 = ksys::phys::ContactPointInfo::make(heap, 0x80, sead::SafeString::cEmptyString, 0, 0, 0);
    if (!_60)
        return false;
    _60->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
    _60->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
    _60->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _60->subscribeLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    _60->subscribeLayer(ksys::phys::ContactLayer::EntityWater);

    {
        ksys::phys::SphereParam param;
        param.name = "Water Core Entity";
        param.motion_type = ksys::phys::MotionType::Dynamic;
        param.toi = true;
        param.radius = 0.15f;
        param.common.material = ksys::phys::Material::Water;
        param.common.sub_material = "Water";
        param.contact_layer = ksys::phys::ContactLayer::EntityObject;
        const f32 volume = std::pow(mArg._20, 3.0f) * 4.1887903f;
        param.mass = volume * ksys::world::Manager::instance()->getElementHolderMaybe()->sub_7100D9A074();
        if (param.mass > 210.0f)
            param.mass = 210.0f;
        _58 = ksys::phys::SphereRigidBody::make(&param, heap);
    }
    if (!_58)
        return false;

    _58->setUserTag(nullptr);
    _58->setContactPointInfo(_60);
    _58->setFlag200();
    _58->setFlag1000000();
    _58->clearFlag2000000(false);
    _58->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    _58->setLinearVelocity(mArg.direction * mArg._24, sead::Mathf::epsilon());
    _58->addToWorld();
    _50->setLinkedRigidBody(_58);

    if (!(mArg.flags & 2)) {
        const char* effect;
        if (mArg.flags & 8)
            effect = "Chemical_Water_Ibutsu";
        else if (mArg.flags & 0x10)
            effect = "Chemical_Water_Ibutsu_2";
        else if (mArg.flags & 0x20)
            effect = "Chemical_Water_Ibutsu_3";
        else
            effect = "Chemical_Water";
        _68 = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_38, effect);
        _68.setMatrix(mtx);
    }

    _1a8 = mArg._20 * 0.03f;
    _1ac = sUnk_710250D120[0];
    return true;
}

void ElementWater::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
    if (_58)
        _58->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
    if (!(mArg.flags & 4) && ksys::snd::SoundMgr::instance()) {
        if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
            if (auto* occlusion = mgr->sub_710102C104())
                occlusion->sub_7101037F7C(a);
        }
    }
    if (sUnk_7102620128 && a && fixed) {
        _68.kill();
        _78.kill();
    }
}

f32 ElementWater::m17(ksys::act::Chemical* chemical) {
    const f32 distance = (chemical->_18->m5() - mArg.position).length();
    if (distance < mArg._20)
        return mArg._24;
    return 0.0f;
}

// NON_MATCHING: regalloc in the last expression (s0 / s1 swapped).
f32 ElementWater::m20(ksys::act::Chemical* chemical) {
    sead::Vector3f dir = chemical->sub_7100D9155C() - mArg.position;
    const f32 distance = dir.normalize();
    const f32 cos = dir.dot(mArg.direction);
    const f32 sin = std::sqrt(sead::Mathf::clamp(1.0f - cos * cos, 0.0f, 1.0f));
    const f32 radius = chemical->_34;
    return sead::Mathf::clamp((radius - (distance * sin - mArg._20)) / (radius + radius), 0.0f, 1.0f);
}

ElementWater* ksys::act::Unk_71024dd490::sub_71010EA040(const ElementWaterCreateArg* arg) {
    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical)
        return nullptr;
    sead::Heap* parent = chemical->_78;
    if (!parent)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&chemical->_28);
    auto* heap = sead::ExpHeap::tryCreate(0x2000, "ElementHolder", parent, 8,
                                          sead::Heap::cHeapDirection_Forward, true);
    if (!heap) {
        if (!(chemical->_84 & 4))
            elementEmitMaybe();
        return nullptr;
    }
    auto* element = new (parent, std::nothrow_t()) ElementWater(*arg, heap);
    if (!element) {
        elementEmitMaybe();
        heap->destroy();
        return nullptr;
    }
    if (mMaxElementHeapSize < heap->getSize())
        mMaxElementHeapSize = heap->getSize();
    if (!element->mHolder) {
        elementEmitMaybe();
        element->m32();
        delete element;
        return nullptr;
    }
    return element;
}
