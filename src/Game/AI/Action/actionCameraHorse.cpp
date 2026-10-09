#include "Game/AI/Action/actionCameraHorse.h"
#include "KingSystem/System/VFRValue.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include <cmath>
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraHorse::CameraHorse(const InitArg& arg) : CameraAction(arg) {}

CameraHorse::~CameraHorse() = default;

// NON_MATCHING: _261 / _262 are cleared with one 16-bit store (two byte stores in the original)
// and the select of bit 2 has its operands swapped
void CameraHorse::m33() {
    sub_710076F638();

    _260.reset(2);
    if (auto* camera = getCamera()) {
        if (camera->_860._800.sub_710079BFB0(2) && camera->_860._7fc.sub_710079C0CC(2))
            _260.set(2);
        else
            _260.reset(2);
    }

    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    _4c = stick.x == 0.0f && stick.y == 0.0f ? 0.0f : 45.0f;

    if (auto* start = mStartCus_s) {
        _e0._0 = 0;
        _e0._10 = start;
        _e0._8 = -sead::Mathf::piHalf();
        _e0._4 = *start * sead::Mathf::pi();
        _f8._0 = 0;
        _f8._8 = -sead::Mathf::piHalf();
        _f8._10 = start;
        _f8._4 = *start * sead::Mathf::pi();
    }

    _134 = 0;
    _13c = 0;
    _140 = 0;
    _54 = 0;

    if (auto* camera = getCamera()) {
        if (camera->_860._260.hasProc())
            camera->_860._7f8.reset(1);
        const bool flag = camera->_860._7f8.isOn(1);
        _261.makeAllZero();
        _262 = 0;
        if (_260.isOn(2) && flag)
            _260.set(4);
        else
            _260.reset(4);
        _260.reset(1);
        _b4 = (camera->_860._0._c - camera->_860._0._0).length();
        _bc = 0;
    }
}

// NON_MATCHING: the original loads the rate pointer in the two branches (tbnz) instead of selecting the address,
// and swaps the registers of the two loads before the first fsub.
void CameraHorse::sub_7100771B94() {
    const f32 rate = *(_261.isOn(2) ? mSideOffsetCus_s : mSideOffsetCusNoInput_s);
    const f32 t1 = sub_710092523C(sub_71009251C4(getCameraActor()), rate);
    _9c = _9c + (_84 - _9c) * t1;
    const f32 t2 = sub_710092523C(sub_71009251C4(getCameraActor()), 0.4f);
    _a0 = t2 * (_88 - _a0) + _a0;
}

void CameraHorse::m36() {
    getStaticParam(&mLatSlow_s, "latSlow");
    getStaticParam(&mLatFast_s, "latFast");
    getStaticParam(&mLatCus_s, "latCus");
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLngCusSlow_s, "lngCusSlow");
    getStaticParam(&mLngCusFast_s, "lngCusFast");
    getStaticParam(&mLngCusParallel_s, "LngCusParallel");
    getStaticParam(&mLngCusVertical_s, "LngCusVertical");
    getStaticParam(&mRadiusSlow_s, "radiusSlow");
    getStaticParam(&mRadiusFast_s, "radiusFast");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mSideOffsetSlow_s, "sideOffsetSlow");
    getStaticParam(&mSideOffsetFast_s, "sideOffsetFast");
    getStaticParam(&mSideOffsetCus_s, "sideOffsetCus");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mAtHCusSlow_s, "AtHCusSlow");
    getStaticParam(&mAtHCusFast_s, "AtHCusFast");
    getStaticParam(&mAtVCusSlow_s, "AtVCusSlow");
    getStaticParam(&mAtVCusFast_s, "AtVCusFast");
    getStaticParam(&mFovySlow_s, "fovySlow");
    getStaticParam(&mFovyFast_s, "fovyFast");
    getStaticParam(&mFovyCus_s, "fovyCus");
    getStaticParam(&mStartCus_s, "startCus");
    getStaticParam(&mSpeedMin_s, "speedMin");
    getStaticParam(&mSpeedMax_s, "speedMax");
    getStaticParam(&mHandlingRateCoefficient_s, "HandlingRateCoefficient");
    getStaticParam(&mHandlingRateReturnSpeed_s, "HandlingRateReturnSpeed");
    getStaticParam(&mSideOffsetCusNoInput_s, "sideOffsetCusNoInput");
}

void CameraHorse::sub_710076F638() {
    _238 = sub_7100924D80(*mLngCusSlow_s);
    _23c = sub_7100924D80(*mLngCusFast_s);
    _240 = sub_7100924D80(*mLngCusParallel_s);
    _244 = sub_7100924D80(*mLngCusVertical_s);
    _248 = sub_7100924D80(*mAtHCusSlow_s);
    _24c = sub_7100924D80(*mAtHCusFast_s);
    _250 = sub_7100924D80(*mAtVCusSlow_s);
    _254 = sub_7100924D80(*mAtVCusFast_s);
    _258 = sead::Mathf::clampMin(*mHandlingRateCoefficient_s, 0.0f);
    _25c = sead::Mathf::clamp(*mHandlingRateReturnSpeed_s, 0.0f, 1.0f);
}

void CameraHorse::sub_71007710F8(f32* out) {
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        *out = angleStuff(*mLatSlow_s + (*mLatFast_s - *mLatSlow_s) * _50);
        const sead::Vector3f pos = camera->_860._0._c + polar.sub_7100923254();
        *out = angleStuff(sub_710092738C(camera->_860._0._c, pos) + *out);
    }
}

// NON_MATCHING: load order only (the original loads the stick component into a callee-saved register before
// the first call; ours loads it after).
void CameraHorse::sub_71007711DC(f32* out) {
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        *out = polar._4;
        sead::Vector2f stick = sead::Vector2f::zero;
        sub_7100924F08(&stick);
        ksys::VFRValue rate(sub_7100927238() * stick.y * sub_7100927228());
        rate.updateStats();
        *out = angleStuff(angleStuff(rate.mean) + *out);
    }
}

// NON_MATCHING: load order only (the original loads the stick component into a callee-saved register before
// the first call; ours loads it after).
void CameraHorse::sub_7100771684(f32* out) {
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        *out = polar._8;
        sead::Vector2f stick = sead::Vector2f::zero;
        sub_7100924F08(&stick);
        ksys::VFRValue rate(sub_71009272A8() * stick.x * sub_7100927230());
        rate.updateStats();
        *out = angleStuff(angleStuff(rate.mean) + *out);
    }
}

// NON_MATCHING: state branch layout differs.
void CameraHorse::sub_7100770474() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    if (stick.x != 0.0f || stick.y != 0.0f) {
        _263 = 2;
        return;
    }
    if (u32(_263) - 1 < 3)
        return;
    if (_263 == 0) {
        if (player->m290())
            _263 = 1;
        return;
    }
    if (camera->_860._260.hasProc()) {
        _263 = 3;
    } else if (_260.isOn(2)) {
        _263 = 0;
    } else {
        camera = getCamera();
        _263 = camera && camera->_860._7f8.isOn(1) ? 2 : 1;
    }
}

// NON_MATCHING: the state switch uses comparisons instead of a jump table.
void CameraHorse::sub_710077066C(u8 previous_state) {
    const u8 state = _263;
    if (state == previous_state)
        return;
    auto* camera = getCamera();
    if (state == 2) {
        if (camera)
            camera->_860._7f8.set(1);
    } else if (camera) {
        camera->_860._7f8.reset(1);
    }
    switch (_263) {
    case 0:
        sub_7100770B98();
        break;
    case 1:
    case 2:
        sub_7100770DA8();
        break;
    case 3:
        sub_7100770DA8();
        _110.sub_710079C384(10.0f, 0.0f);
        break;
    }
    _130 = 1.0f;
}

// NON_MATCHING: minimum and value loads are reversed.
void CameraHorse::sub_7100771008(f32* out) {
    switch (_263) {
    case 0:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            *out = polar._4;
        }
        break;
    case 1:
        sub_71007710F8(out);
        break;
    case 2:
        sub_71007711DC(out);
        break;
    case 3:
        sub_71007712B0(out);
        break;
    }
    if (*out < _58)
        *out = _58;
    else if (*out > _5c)
        *out = _5c;
    *out = angleStuff(*out);
}

void CameraHorse::sub_7100771480(f32* out) {
    switch (_263) {
    case 0:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            *out = polar._8;
        }
        break;
    case 1:
        sub_710077154C(out);
        break;
    case 2:
        sub_7100771684(out);
        break;
    case 3:
        sub_7100771758(out);
        break;
    }
}

// NON_MATCHING: the vertical special case uses a constant selection table.
void CameraHorse::sub_71007712B0(f32* out) {
    auto* camera = getCamera();
    if (!camera || !camera->_860._260.hasProc())
        return;
    auto* target = sead::DynamicCast<ksys::act::Actor>(camera->_860._260.getProc(nullptr, nullptr));
    if (!target)
        return;
    auto* player = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    if (!player)
        return;
    const sead::Vector3f direction = player->getMtx().getTranslation() - target->getMtx().getTranslation();
    f32 latitude;
    if (direction.x == 0.0f && direction.z == 0.0f)
        latitude = direction.y < 0.0f ? -180.0f : 180.0f;
    else
        latitude = sead::Mathf::rad2deg(std::atan2(direction.y, std::sqrt(direction.x * direction.x + direction.z * direction.z)));
    *out = angleStuff(latitude);
}

// NON_MATCHING: zero result storage uses a float register.
void CameraHorse::sub_710077154C(f32* out) {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    auto* player = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    if (!player)
        return;
    const sead::Vector3f direction = -player->getMtx().getBase(2);
    if (direction.x == 0.0f && direction.z == 0.0f)
        *out = 0.0f;
    else
        *out = angleStuff(sead::Mathf::rad2deg(std::atan2(direction.x, direction.z)));
}

// NON_MATCHING: cross and dot scheduling and saved float registers differ.
void CameraHorse::sub_7100771758(f32* out) {
    auto* camera = getCamera();
    if (!camera || !camera->_860._260.hasProc())
        return;
    auto* target = sead::DynamicCast<ksys::act::Actor>(camera->_860._260.getProc(nullptr, nullptr));
    if (!target)
        return;
    auto* player = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    if (!player)
        return;
    const sead::Vector3f base = player->getMtx().getBase(2);
    const sead::Vector3f forward(base.x, 0.0f, base.z);
    if (forward.x == 0.0f && forward.z == 0.0f) {
        *out = 0.0f;
        return;
    }
    *out = angleStuff(sead::Mathf::rad2deg(std::atan2(forward.x, forward.z)));
    const sead::Vector3f difference = player->getMtx().getTranslation() - target->getMtx().getTranslation();
    const sead::Vector3f direction(difference.x, 0.0f, difference.z);
    if (direction.x == 0.0f && direction.z == 0.0f)
        return;
    sead::Vector3f cross;
    cross.setCross(forward, direction);
    const f32 angle = std::atan2(cross.length(), forward.dot(direction));
    const f32 sign = cross.y > 0.0f ? 1.0f : -1.0f;
    *out = angleStuff(*out + sign * (sead::Mathf::rad2deg(angle) * 0.8f));
}

// NON_MATCHING: polar loads and float registers differ.
void CameraHorse::sub_7100770B98() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _a4 = _60;
    _a8 = angleStuff(polar._4 - _60);
    f32 duration = 0.0f;
    if (angleStuff(_a8) != angleStuff(0.0f))
        duration = sead::Mathf::clampMin((_a8 > 0.0f ? _a8 : -_a8) * 0.5f, 10.0f);
    _ac = _64;
    _b0 = angleStuff(0.0f);
    _b4 = _68;
    _b8 = polar._0 - _68;
    if (_b8 != 0.0f)
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), (_b8 > 0.0f ? _b8 : -_b8) * 0.5f);
    _c0 = _6c;
    _cc = camera->_860._0._c - _6c;
    if (_cc != sead::Vector3f(0.0f, 0.0f, 0.0f))
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), _cc.length() * 0.5f);
    _d8 = _8c;
    _dc = camera->_860._0._24 - _8c;
    if (_dc != 0.0f) {
        const f32 degrees = sead::Mathf::rad2deg(_dc);
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), degrees > 0.0f ? degrees : -degrees);
    }
    _110.sub_710079C384(duration, 0.0f);
}

// NON_MATCHING: polar loads and float registers differ.
void CameraHorse::sub_7100770DA8() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _a4 = _60;
    _a8 = angleStuff(polar._4 - _60);
    f32 duration = 0.0f;
    if (angleStuff(_a8) != angleStuff(0.0f))
        duration = sead::Mathf::clampMin((_a8 > 0.0f ? _a8 : -_a8) * 0.4f, 10.0f);
    _ac = _64;
    _b0 = angleStuff(polar._8 - _64);
    if (angleStuff(_b0) != angleStuff(0.0f))
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), (_b0 > 0.0f ? _b0 : -_b0) * 0.2f);
    _b4 = _68;
    _b8 = polar._0 - _68;
    if (_b8 != 0.0f)
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), (_b8 > 0.0f ? _b8 : -_b8) * 0.5f);
    _c0 = _6c;
    _cc = camera->_860._0._c - _6c;
    if (_cc != sead::Vector3f(0.0f, 0.0f, 0.0f))
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), _cc.length() * 0.5f);
    _d8 = _8c;
    _dc = camera->_860._0._24 - _8c;
    if (_dc != 0.0f) {
        const f32 degrees = sead::Mathf::rad2deg(_dc);
        duration = sead::Mathf::max(std::fmax(duration, 10.0f), degrees > 0.0f ? degrees : -degrees);
    }
    _110.sub_710079C384(duration, 0.0f);
}

// NON_MATCHING: cached input flag branch layout differs.
void CameraHorse::sub_7100771C30(f32* out) {
    *out = *mSideOffsetSlow_s + (*mSideOffsetFast_s - *mSideOffsetSlow_s) * _50;
    auto* ridden_actor = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    f32 speed;
    if (auto* motorcycle = sead::DynamicCast<act::Motorcycle>(ridden_actor)) {
        speed = motorcycle->speedStuff_1();
        if (motorcycle->_bb4 == 0.0f)
            _261.reset(2);
        else
            _261.set(2);
    } else {
        speed = _54;
    }
    *out *= speed;
}

void CameraHorse::sub_7100771DA8(f32* out) {
    *out = *mOffsetYMin_s + (*mOffsetYMax_s - *mOffsetYMin_s) * _50;
    auto* ridden_actor = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    if (!ridden_actor)
        return;
    ksys::act::ActorConstDataAccess accessor(ridden_actor);
    if (sub_7100926DF0(accessor) || sub_7100926E7C(accessor))
        *out += sub_71009221D4();
    else if (ksys::act::hasTag(ridden_actor, ksys::act::tags::IsVehicle))
        *out += sub_71009221DC();
}

// NON_MATCHING: saved registers and vector stores differ.
void CameraHorse::sub_7100770574() {
    sub_7100771C30(&_84);
    sub_7100771DA8(&_88);
    sub_7100771B94();
    sub_71007719C4();
    {
        ksys::act::ActorConstDataAccess accessor;
        sub_7100926A9C(&accessor);
        _90 = accessor.getActorMtx().getBase(0);
        _90.y = 0.0f;
        const f32 length = _90.length();
        if (length > 0.0f)
            _90 *= _9c / length;
    }
    _90.y += _a0;
}

// NON_MATCHING: the compiler removes the discarded distance calculation and sqrt fallback.
void CameraHorse::sub_71007719C4() {
    sead::Vector3f end = _78;
    sead::Vector3f direction;
    {
        ksys::act::ActorConstDataAccess accessor;
        sub_7100926A9C(&accessor);
        direction = accessor.getActorMtx().getBase(0);
        direction.y = 0.0f;
        const f32 length = direction.length();
        if (length > 0.0f)
            direction *= _9c / length;
    }
    end += sead::Vector3f(direction.x, _a0 + direction.y, direction.z);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::Camera);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    query.setStartAndEnd(_78, end);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&end);
        std::sqrt((end - _78).squaredLength());
    }
}

// NON_MATCHING: smoothing arithmetic, vector copies and register allocation differ.
void CameraHorse::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    auto* ridden_actor = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    if (!ridden_actor)
        return;
    const sead::Vector3f forward = ridden_actor->getMtx().getBase(2);
    if (!_260.isOn(1)) {
        _263 = 4;
        sub_710077002C();
        _260.set(1);
    }
    _262 = _261.getDirect();
    _261.makeAllZero();
    sub_71007701C4();
    sub_71007702C8();
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_58, &_5c);
    if (camera->_860._260.hasProc())
        _261.set(1);
    const u8 previous_state = _263;
    sub_7100770474();
    sub_7100771480(&_64);
    if (auto* ridden = sead::DynamicCast<ksys::act::Actor>(
            ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)))
        _78 = ridden->getMtx().getTranslation();
    sub_7100770574();
    _6c = _78 + _90;
    sub_7100771008(&_60);
    _68 = *mRadiusSlow_s + (*mRadiusFast_s - *mRadiusSlow_s) * _50;
    if (sub_7100926E0C())
        _68 += sub_71009221E4();
    _8c = *mFovySlow_s + (*mFovyFast_s - *mFovySlow_s) * _50;
    sub_710077066C(previous_state);
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sead::Vector2f stick(0.0f, 0.0f);
    sub_7100924F08(&stick);
    if (stick.x == 0.0f && stick.y == 0.0f) {
        ksys::Timer::update(&_4c, -1.0f);
        if (_4c < 0.0f)
            _4c = 0.0f;
    } else {
        _4c = 45.0f;
    }
    if (stick.x != 0.0f || stick.y != 0.0f)
        _260.set(4);
    if (camera->_860._7f8.isOn(1) && !_260.isOn(4) && player->m290()) {
        camera->_860._7f8.reset(1);
        _260.set(4);
    }
    if (stick.x != 0.0f || stick.y != 0.0f)
        camera->_860._7f8.set(1);
    ksys::VFR::chase(&_e0._8, sead::Mathf::piHalf(), _e0._4);
    _e0._0 = (std::sin(_e0._8) + 1.0f) * 0.5f;
    sub_710077071C();
    _110.sub_710079C408();
    ksys::VFR::lerp(&_130, 0.0f, 0.1f);
    const f32 transition = _130;
    if (_263 == 3) {
        const f32 rate = sub_7100791E44(0.6f);
        _ac = angleStuff(_ac + angleStuff(rate * angleStuff(_64 - _ac)));
    } else if (_263 == 2) {
        _ac = _64;
    } else if (_263 == 1) {
        f32 heading = 0.0f;
        if (forward.x != 0.0f || forward.z != 0.0f)
            heading = angleStuff(sead::Mathf::rad2deg(std::atan2(forward.x, forward.z)));
        const f32 wrapped_heading = angleStuff(sub_7100922530(heading));
        const f32 rate = sub_7100791E44(_238 + _50 * (_23c - _238));
        const f32 difference = angleStuff(polar._8 - wrapped_heading);
        const f32 magnitude = difference > 0.0f ? difference : -difference;
        const f32 blend = (std::sin(sead::Mathf::deg2rad(magnitude) - sead::Mathf::piHalf()) + 1.0f) * 0.5f;
        _ac = angleStuff(_ac + angleStuff(angleStuff(_64 - _ac) * rate * (_240 + blend * (_244 - _240))));
    }
    polar._8 = angleStuff(_ac + angleStuff(transition * _b0));
    if (_263 == 1 || _263 == 3) {
        const f32 rate = sub_7100791E44(*mLatCus_s);
        _a4 = angleStuff(_a4 + angleStuff(rate * angleStuff(_60 - _a4)));
    } else if (_263 == 2) {
        _a4 = _60;
    }
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(_a4 + angleStuff(transition * _a8))));
    _b4 = _b4 + sub_7100791E44(*mRadiusCus_s) * (_68 - _b4);
    polar._0 = _b4 + transition * _b8;
    const sead::Vector3f ridden_position = camera->_860._270.getTranslation();
    const sead::Vector3f& target = sub_7100928868(camera->_860._164);
    const f32 horizontal = sead::Mathf::clamp(std::sqrt(
        (ridden_position.x - target.x) * (ridden_position.x - target.x) +
        (ridden_position.z - target.z) * (ridden_position.z - target.z)), 0.0f, 1.0f);
    const f32 vertical = sead::Mathf::clamp(
        ridden_position.y - target.y > 0.0f ? ridden_position.y - target.y : -(ridden_position.y - target.y), 0.0f, 1.0f);
    const f32 horizontal_rate = sub_7100791E44(_248 + horizontal * (_24c - _248));
    const f32 vertical_rate = sub_7100791E44(_250 + vertical * (_254 - _250));
    _c0.x = _c0.x + horizontal_rate * (_6c.x - _c0.x);
    _c0.y = _c0.y + vertical_rate * (_6c.y - _c0.y);
    _c0.z = _c0.z + horizontal_rate * (_6c.z - _c0.z);
    camera->_860._0._c = transition * _cc + _c0;
    _d8 = _d8 + _e0._0 * sub_7100791E44(*mFovyCus_s) * (_8c - _d8);
    camera->_860._0._24 = _d8 + transition * _dc;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    _bc = _bc + sub_7100791E44(0.1f) * (0.0f - _bc);
    polar._0 += _bc;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->sub_71007953C8();
}

// NON_MATCHING: translation copying and saved registers differ.
void CameraHorse::sub_710077002C() {
    if (auto* ridden_actor = sead::DynamicCast<ksys::act::Actor>(
            ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)))
        _78 = ridden_actor->getMtx().getTranslation();
    sub_7100771C30(&_84);
    sub_7100771DA8(&_88);
    _9c = _84;
    _a0 = _88;
    sub_71007719C4();
    {
        ksys::act::ActorConstDataAccess accessor;
        sub_7100926A9C(&accessor);
        _90 = accessor.getActorMtx().getBase(0);
        _90.y = 0.0f;
        const f32 length = _90.length();
        if (length > 0.0f)
            _90 *= _9c / length;
    }
    _90.y += _a0;
}

// NON_MATCHING: branch layout and min/max stack slots differ.
void CameraHorse::sub_71007701C4() {
    ksys::act::ActorConstDataAccess accessor;
    sub_7100926A9C(&accessor);
    if (!accessor.hasProc())
        return;
    const sead::Vector3f& velocity = accessor.getVelocity();
    if (ksys::util::sub_71011F1040(velocity))
        return;
    if (*mSpeedMin_s == *mSpeedMax_s) {
        _50 = 0.5f;
        return;
    }
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924C94(*mSpeedMin_s, *mSpeedMax_s, &min, &max);
    _50 = (sead::Mathf::clamp(velocity.length(), min, max) - min) / (max - min);
}

// NON_MATCHING: float registers differ in the handling return path.
void CameraHorse::sub_71007702C8() {
    ksys::act::ActorConstDataAccess accessor;
    sub_7100926A74(&accessor);
    const f32 turn = accessor.getAngVelocity().y;
    const f32 epsilon = sead::Mathf::epsilon();
    if (_263 == 2 || (turn <= epsilon && turn >= -epsilon)) {
        const sead::Vector3f& velocity = accessor.getVelocity();
        if (velocity.x <= epsilon && velocity.x >= -epsilon &&
            velocity.y <= epsilon && velocity.y >= -epsilon &&
            velocity.z <= epsilon && velocity.z >= -epsilon)
            return;
        sead::Mathf::chase(&_54, 0.0f, _25c * sub_71009251C4(getCamera()));
    } else {
        const f32 sign = turn > 0.0f ? 1.0f : -1.0f;
        const f32 magnitude = turn > 0.0f ? turn : -turn;
        sead::Mathf::chase(&_54, sign, magnitude * _258 * sub_71009251C4(getCamera()));
    }
}

void CameraHorse::sub_710077071C() {
    if (auto* camera = getCamera()) {
        if (camera->_860._7f8.isOn(1)) {
            _f8._0 = 0.0f;
            _f8._8 = -sead::Mathf::piHalf();
            return;
        }
    }
    ksys::VFR::chase(&_f8._8, sead::Mathf::piHalf(), _f8._4);
    _f8._0 = (std::sin(_f8._8) + 1.0f) * 0.5f;
}

}  // namespace uking::action
