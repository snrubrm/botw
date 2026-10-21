// TU of Camera's 0x820-byte sub-object (Unk_710079a8e8, ctor 0x710079a8e8) and its flag / easing
// helper types (0x710079a8e8-0x710079c5b0): separate from the Camera TU, which calls these out of
// line (e.g. Camera::sub_7100794FD0 tail-calls Unk_710079b62c::sub_710079C0CC).
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include "Game/Actor/actCamera.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/gameSceneSubsysMisc.h"
#include "Game/gameGraphics.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/Sound/sndSound.h"

namespace uking::act {

void Unk_710079a8e8::ListenerState::sub_710079A884() {
    auto* sound = ksys::snd::SoundMgr::instance();
    if (!sound)
        return;
    auto* poser = sound->_58;
    if (!poser)
        return;
    mode = poser->_78;
    _4 = !poser->_70;
    valid = true;
}

void Unk_710079a8e8::ListenerState::sub_710079A8BC() const {
    if (!valid)
        return;
    auto* sound = ksys::snd::SoundMgr::instance();
    if (!sound)
        return;
    if (auto* poser = sound->_58)
        poser->_78 = mode;
}

void Unk_710079a8e8::SavePoint::save(const Unk_710079a8e8& camera) {
    _0 = camera._0;
    _38 = camera._72c._0;
    _3c = camera._39c;
    _6c = camera._3cc;
    _78 = camera._3d8;
}

bool Unk_710079a8e8::SavePoint::restore(Unk_71009214b8* out) const {
    if (!isValid())
        return false;
    *out = _0;
    return true;
}

bool Unk_710079a8e8::SavePoint::isValid() const {
    return _38 >= 0 && _38 < 2;
}

void Unk_710079b62c::sub_710079B62C(u32 mask) {
    _0 |= mask;
}

bool Unk_710079b62c::sub_710079BFB0(u32 mask) const {
    return (_0 & mask) == 0;
}

bool Unk_710079b62c::sub_710079C0CC(u32 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079adc8::sub_710079ADC8(u32 mask) const {
    return (_0 & mask) == 0;
}

void Unk_710079adc8::sub_710079AE20(u32 mask) {
    _0 |= mask;
}

void Unk_710079adc8::sub_710079AE40(u32 mask) {
    _0 &= ~mask;
}

bool Unk_710079adc8::sub_710079AE50(u32 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079c1c8::sub_710079C1C8(u8 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079c1f4::sub_710079C1F4(u8 mask) const {
    return (_0 & mask) != 0;
}

void Unk_710079c1c8::sub_710079C1DC(u8 mask) {
    _0 |= mask;
}

void Unk_710079c1c8::sub_710079C1EC() {
    _0 = 0;
}

void Unk_710079c1f4::sub_710079C208(u8 mask) {
    _0 |= mask;
}

void Unk_710079c1f4::sub_710079C218() {
    _0 = 0;
}

void Unk_710079a8e8::sub_710079AD90() {
    _7f0[0] = -1.0;
    _7f0[1] = -1.0;
}

f32 Unk_710079a8e8::sub_710079ADA0() const {
    if ((_804._0 & 0x6000) == 0x2000)
        return _15c;
    return sub_7100922058();
}

bool Unk_710079a8e8::sub_710079ADBC() const {
    return _804.sub_710079AE50(0x2000);
}

void Unk_710079a8e8::sub_710079AE30() {
    _804.sub_710079AE40(0x2000);
}

void Unk_710079a8e8::sub_710079AEE0() {
    _1a0.set(0.0f, 0.0f, 0.0f);
    _1b8 = angleStuff(0.0f);
    _1bc = angleStuff(0.0f);
    _1c0 = 0.0f;
    _1c4 = 0.0f;
    _1d0.sub_710079C510(1.0f);
}

void Unk_710079a8e8::sub_710079AED0() {
    _804.sub_710079AE40(0x8000);
}

void Unk_710079a8e8::sub_710079B16C() {
    _200.reset();
    auto* attention = ksys::act::Attention::instance();
    if (!attention || !attention->sub_7100D74114())
        return;
    attention->sub_7100D74148(&_200);
    if (!_200.hasProc())
        return;
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (sub_7100925AB8(_200, &mtx))
        _2d0 = mtx;
    sead::Vector3f pos = sead::Vector3f::zero;
    if (sub_7100925D38(_200, &pos))
        _300 = pos;
    sead::Vector3f pos2 = sead::Vector3f::zero;
    if (sub_7100925E88(_200, &pos2))
        _30c = pos2;
    sead::Vector3f pos3 = sead::Vector3f::zero;
    if (sub_7100925FD8(_200, &pos3))
        _318 = pos3;
}

void Unk_710079a8e8::sub_710079B2C4() {
    _210.reset();
    if (auto* attention = ksys::act::Attention::instance())
        attention->sub_7100D747D8(&_210);
}

void Unk_710079a8e8::sub_710079B308(Camera* camera) {
    if (!camera)
        return;
    if (!camera->get1a0() &&
        !(camera->getMapObject() &&
          camera->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        return;
    }
    auto& link = ksys::evt::sub_7100DC85D4(camera);
    if (!link.hasProc())
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.linkAcquire(&_220);
    if (!ksys::util::sub_71011F10F4(accessor.getActorMtx()))
        _324 = accessor.getActorMtx();
}

// NON_MATCHING: the accessor address is kept in an extra callee-saved register (regalloc only).
void Unk_710079a8e8::sub_710079B3C8(Camera* camera) {
    if (!camera || (!camera->get1a0() &&
                    !(camera->getMapObject() &&
                      camera->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))) {
        _230.reset();
        return;
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    sub_710092486C(camera, &accessor);
    if (!accessor.hasProc()) {
        _230.reset();
        return;
    }
    accessor.linkAcquire(&_230);
    const auto& mtx = accessor.getActorMtx();
    if (!ksys::util::sub_71011F10F4(mtx))
        _354 = mtx;
    const auto& pos = accessor.getPreviousPos2();
    if (!ksys::util::sub_71011F1040(pos))
        _384 = pos;
    const auto& pos2 = accessor.getField458_Vec3();
    if (!ksys::util::sub_71011F1040(pos2))
        _390 = pos2;
}

void Unk_710079a8e8::sub_710079B4F0() {}

// NON_MATCHING: the bit 0x80 update computes the reset value first (and / orr order; `!(x <= 0)` fixes it
// but gives csel hi instead of gt).
void Unk_710079a8e8::sub_710079B4F4() {
    auto* player = sub_7100926A14();
    if (player && player->_cf4.isOnBit(2))
        _7fc.sub_710079B62C(4);
    if (_800.sub_710079C0CC(4) || !_7fc.sub_710079C0CC(4))
        return;
    _250 = _210;
    if (!_250.hasProc())
        return;
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (sub_7100925AB8(_250, &mtx))
        _3e4 = mtx;
    const sead::Vector3f dir(_3e4(0, 2), _3e4(1, 2), _3e4(2, 2));
    const sead::Vector3f pos(_3e4(0, 3), _3e4(1, 3), _3e4(2, 3));
    const auto& player_mtx = player->getMtx();
    const sead::Vector3f player_pos(player_mtx(0, 3), player_mtx(1, 3), player_mtx(2, 3));
    if (dir.dot(player_pos - pos) > 0.0f)
        _804.sub_710079AE20(0x80);
    else
        _804.sub_710079AE40(0x80);
}

bool Unk_710079a8e8::sub_710079B63C(u32 mask) const {
    if (_800.sub_710079C0CC(mask))
        return false;
    return _7fc.sub_710079C0CC(mask);
}

void Unk_710079a8e8::sub_710079BAE4() {
    auto* subsys = GameSceneSubsys5::instance();
    if (!subsys)
        return;
    const auto& pos = subsys->sub_7100905C38();
    if (!ksys::util::isVectorInvalid(pos))
        _4cc = pos;
    const auto pos2 = subsys->sub_7100905D58();
    if (!ksys::util::isVectorInvalid(pos2))
        _4d8 = pos2;
}

void Unk_710079a8e8::sub_710079BBA8() {
    auto* player = sub_7100926A14();
    if (!player)
        return;
    ksys::act::PlayerLink* link = player;
    auto* motorcycle = sead::DynamicCast<Motorcycle>(link->m382());
    if (!motorcycle)
        return;
    _49c = motorcycle->getMainBody()->getTransform();
    _7fc._0 |= 0x400000;
}

void Unk_710079a8e8::sub_710079BC8C() {
    _170 = false;
    _180 = false;
}

void Unk_710079a8e8::sub_710079BD2C() {
    _240.reset();
    _804.sub_710079AE40(0x800);
}

void Unk_710079a8e8::sub_710079BD5C() {
    _7fc.sub_710079B62C(0x20);
}

void Unk_710079a8e8::sub_710079BD6C(f32 value) {
    _190 = sead::Mathf::clamp(value, 0.0f, 1.0f);
}

void Unk_710079a8e8::sub_710079BD98() {
    _190 = -1.0;
}

bool Unk_710079a8e8::sub_710079BDA4() const {
    return _190 >= 0.0f && _190 <= 1.0f;
}

// NON_MATCHING: C++17 assignment evaluates the value before the core-index getter calls.
void Unk_710079a8e8::sub_710079BDC4(const f32& value) {
    _6f0[sead::CoreInfo::getPlatformCoreId(sead::CoreInfo::getCurrentCoreId())] = value;
}

void Unk_710079a8e8::sub_710079BE34() {
    _6f0.fill(0);
}

f32 Unk_710079a8e8::sub_710079BE40() const {
    f32 result = 0;
    f32 maximum = -1.0f;
    const f32 a = sead::Mathf::abs(_6f0[0]);
    if (a > maximum) {
        maximum = a;
        result = _6f0[0];
    }
    const f32 b = sead::Mathf::abs(_6f0[1]);
    if (b > maximum) {
        maximum = b;
        result = _6f0[1];
    }
    if (sead::Mathf::abs(_6f0[2]) > maximum)
        result = _6f0[2];
    return result;
}

void Unk_710079a8e8::sub_710079BEA8() {
    _72c._4._38 = 2;
}

void Unk_710079a8e8::sub_710079BEB4() {
    _7b4.valid = false;
}

bool Unk_710079a8e8::sub_710079BEBC() const {
    return _7e0 != -1.0f;
}

f32 Unk_710079a8e8::sub_710079BF0C() const {
    return _7e0;
}

void Unk_710079a8e8::sub_710079BF14() {
    _7e0 = -1.0;
}

bool Unk_710079a8e8::sub_710079BF20() const {
    return _7e4 != -1.0f;
}

void Unk_710079a8e8::sub_710079BF34(f32 value) {
    if (value < 0.0f || std::isnan(value))
        return;
    _7e4 = value;
}

void Unk_710079a8e8::sub_710079BF58() {
    _7e4 = -1.0;
}

void Unk_710079a8e8::sub_710079C0AC() {
    if (!_7fc.sub_710079C0CC(0x80000))
        _804.sub_710079AE40(0x10000);
    else
        _804.sub_710079AE20(0x10000);
}


void Unk_710079a8e8::sub_710079C0DC(int idx, f32 value) {
    _7f0[idx] = value;
}

bool Unk_710079a8e8::sub_710079C0F4(f32* out) const {
    for (f32 value : _7f0) {
        if (value >= 0.0f) {
            *out = value;
            return true;
        }
    }
    return false;
}

bool Unk_710079a8e8::sub_710079C120(u8 mask) const {
    return _80c.isOn(mask);
}

bool Unk_710079a8e8::sub_710079C134(u8 mask) const {
    return _80c.isOff(mask);
}

void Unk_710079a8e8::sub_710079C148(u8 mask) {
    _80c.set(mask);
}

void Unk_710079a8e8::sub_710079C158(u8 mask, bool on) {
    _80c.change(mask, on);
}

void Unk_710079a8e8::sub_710079C17C() {
    _80c.makeAllZero();
}

bool Unk_710079a8e8::sub_710079C184(u32 mask) const {
    if (_808.sub_710079AE50(mask))
        return false;
    return _804.sub_710079AE50(mask);
}


void Unk_710079a8e8::sub_710079ADD8(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value <= 0.0f)
        return;
    _15c = value;
    _804.sub_710079AE20(0x2000);
}

f32 Unk_710079a8e8::sub_710079AE60() const {
    if (_804.sub_710079AE50(0x8000))
        return _160;
    if (auto* graphics = Graphics::instance())
        return graphics->sub_7100F35F38();
    return sub_7100922064();
}

void Unk_710079a8e8::sub_710079AE88(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value <= 0.0f)
        return;
    _160 = value;
    _804.sub_710079AE20(0x8000);
}

void Unk_710079a8e8::sub_710079BC98() {
    // C++14 evaluation order: the original evaluates the destination first
    _240.operator=(_230);
    _39c = _354;
    _3cc = _384;
    _3d8 = _390;
    _804.sub_710079AE20(0x800);
}

void Unk_710079a8e8::sub_710079BED0(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value < 0.0f)
        return;
    _7e0 = value;
}

f32 Unk_710079a8e8::sub_710079BF64(const f32& angle, bool a2) {
    if (!(_7fc._0 & 0x80000)) {
        sub_710079BFC0(angle, _804._0 & 0x10000, a2);
        _7fc._0 |= 0x80000;
    }
    return _7e8;
}

// NON_MATCHING: the original loads `angle` before _7ec for the first difference (load order only).
void Unk_710079a8e8::sub_710079BFC0(const f32& angle, bool smooth, bool a3) {
    if (smooth && !a3) {
        const f32 diff = angleStuff(_7ec - angle);
        if (sub_71009226D8(diff) > 0.01f) {
            const bool positive = angleStuff(diff) > angleStuff(0.0f);
            _7ec = angleStuff(angle + (positive ? 0.01f : -0.01f));
        }
    } else {
        _7ec = angle;
    }
    const f32 rad = sead::Mathf::deg2rad(_7ec);
    const sead::Vector3f dir(std::sin(rad), 0.0f, std::cos(rad));
    _7e8 = sub_7100927AE0(dir);
}

}  // namespace uking::act
