#include "Game/AI/Action/actionCameraEventMultiTalk.h"
#include <math/seadMathCalcCommon.h>
#include <limits>
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

// NON_MATCHING: the native pre-construction array memset is absent from natural member initialization.
CameraEventMultiTalk::CameraEventMultiTalk(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMultiTalk::~CameraEventMultiTalk() = default;

void CameraEventMultiTalk::m43() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_318, &_31c);
    _320 = sead::Mathf::clampMin(*mRadiusOffset_s, 0.0f);
    _324 = sub_7100924D50(sead::Mathf::deg2rad(*mFovy_d));
    _328 = sead::Mathf::clampMin(*mConnect_s, 0.0f);
    _b0[0].sub_7100924238(mTargets_d[0]);
    _b0[1].sub_7100924238(mTargets_d[1]);
    _b0[2].sub_7100924238(mTargets_d[2]);
    _260 = 0;
    _32c.makeAllZero();
}

// NON_MATCHING: input and vector smoothing register allocation differs.
void CameraEventMultiTalk::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;
    sub_7100765C78();
    for (auto& target : _b0) {
        if (target.status != 0)
            target.sub_710092464C();
    }
    sub_7100765D60();
    if (_32c.isOff(1))
        return;
    sub_7100765E84();
    sub_7100765FA8();
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    _90.sub_710079C408();
    const f32 blend = 1.0f - _90._18;
    const f32 latitude_input = stick.y * sub_7100927238() * sub_7100927228();
    _58 += latitude_input * *mLatStickScale_s;
    _58 = sead::Mathf::clamp(_58, _318, _31c);
    polar._4 = angleStuff(sub_7100924CAC(_58 + blend * _5c));
    const f32 longitude_input = stick.x * sub_71009272A8() * sub_7100927230();
    polar._8 = angleStuff(polar._8 + longitude_input * *mLngStickScale_s);
    f32 rate = sub_7100791E44(0.6f);
    _60 += (_4c - _60) * rate;
    camera->_860._0._c = _60 + _6c * blend;
    camera->_860._0._24 = sub_7100924D50(_324 + blend * _80);
    const f32 distance = (_4c - camera->_860._2b8).length() + _320;
    rate = sub_7100791E44(0.6f);
    _78 += (distance - _78) * rate;
    act::Unk_71009214b8 state = camera->_860._0;
    state._c = _4c;
    act::Unk_7100922700 framing = polar;
    framing._0 = distance;
    framing._4 = angleStuff(_58);
    state._0 = _4c + framing.sub_7100923254();
    state._24 = _324;
    state._28 = 0.0f;
    f32 required = sead::Mathf::clampMin(
        state.sub_710092156C(0.85f, 0.85f, camera->_860._2b8), 0.0f);
    for (const auto& target : _b0) {
        if (target.status != 0) {
            const f32 radius = state.sub_710092156C(0.85f, 0.85f, target.previousPos);
            required = required > radius ? required : radius;
        }
    }
    rate = sub_7100791E44(0.4f);
    if (_88 < required) {
        _88 += (required - _88) * rate;
    } else if ((stick.x != 0.0f || stick.y != 0.0f) && _88 > required + 1.0f) {
        _88 += (required + 1.0f - _88) * rate;
    }
    polar._0 = _78 + _88 + blend * _7c;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._28 = blend * _84;
    if (blend <= std::numeric_limits<f32>::epsilon() &&
        blend >= -std::numeric_limits<f32>::epsilon())
        setFinished();
}

void CameraEventMultiTalk::m46() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mRadiusOffset_s, "RadiusOffset");
    getStaticParam(&mConnect_s, "Connect");
    getDynamicParam_2(&mFovy_d, "Fovy");
    const sead::SafeString specify("ActorSpecify");
    const sead::SafeString actor("ActorName");
    const sead::SafeString unique("UniqueName");
    sead::FixedSafeString<16> specify_name;
    sead::FixedSafeString<16> actor_name;
    sead::FixedSafeString<16> unique_name;
    for (s32 i = 0; i < 3; ++i) {
        specify_name.format("%s%d", specify.cstr(), i + 1);
        actor_name.format("%s%d", actor.cstr(), i + 1);
        unique_name.format("%s%d", unique.cstr(), i + 1);
        getDynamicParam_2(&mTargets_d[i].selector, specify_name);
        getDynamicParam(&mTargets_d[i].actorName, actor_name);
        getDynamicParam(&mTargets_d[i].uniqueName, unique_name);
    }
}

void CameraEventMultiTalk::sub_7100765C78() {
    if (_32c.isOn(1))
        return;
    auto* camera = getCamera();
    if (!camera)
        return;
    bool ready = true;
    for (auto& target : _b0) {
        if (target.selector != -1 && target.status == 0) {
            target.sub_71009242AC(camera);
            ready &= target.status != 0;
        }
    }
    if (ready)
        _32c.set(1);
}

void CameraEventMultiTalk::sub_7100765D60() {
    if (_32c.isOn(1))
        return;
    const s32 limit = sub_7100922088();
    if (_260 >= limit)
        return;
    ++_260;
    if (limit > _260)
        return;
    auto* actor = getActor();
    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(actor, &flow, &entry);
    sead::FixedSafeString<128> path;
    getActiveEventFlowPath(actor, &path);
    setFailed();
}

void CameraEventMultiTalk::sub_7100765E84() {
    sead::Vector3f sum = sead::Vector3f::zero;
    if (auto* camera = getCamera()) {
        sum += camera->_860._2ac;
        f32 count = 1.0f;
        for (const auto& target : _b0) {
            if (target.status != 0) {
                sum += target.position;
                count += 1.0f;
            }
        }
        _4c = sum * (1.0f / count) - camera->_860._2ac + camera->_860._2b8;
    }
}

// NON_MATCHING: typed state copies, vector arithmetic and target iteration scheduling differ.
void CameraEventMultiTalk::sub_7100765FA8() {
    if (_32c.isOn(2))
        return;
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _58 = sead::Mathf::clamp(polar._4, _318, _31c);
    _5c = angleStuff(polar._4 - _58);
    _60 = _4c;
    _6c = camera->_860._0._c - _4c;
    _78 = (_4c - camera->_860._2b8).length() + _320;
    _78 = sub_7100924D40(_78);
    _80 = camera->_860._0._24 - _324;
    _84 = camera->_860._0._28;
    act::Unk_7100922700 adjusted = polar;
    adjusted._0 = _78;
    act::Unk_71009214b8 state = camera->_860._0;
    state._c = _60;
    state._0 = _60 + adjusted.sub_7100923254();
    state._24 = _324;
    state._28 = 0.0f;
    _88 = 0.0f;
    f32 required = state.sub_710092156C(0.8f, 0.8f, camera->_860._2b8);
    _88 = _88 > required ? _88 : required;
    for (const auto& target : _b0) {
        if (target.status != 0) {
            required = state.sub_710092156C(0.8f, 0.8f, target.previousPos);
            _88 = _88 > required ? _88 : required;
        }
    }
    _7c = polar._0 - (_78 + _88);
    f32 amount = sead::Mathf::clampMin(sead::Mathf::abs(_5c) * 0.5f, 0.0f);
    const f32 offset = _6c.length() * 2.0f;
    amount = amount > offset ? amount : offset;
    const f32 radius = sead::Mathf::abs(_7c) * 2.0f;
    amount = amount > radius ? amount : radius;
    const f32 fovy = sead::Mathf::abs(sead::Mathf::rad2deg(_80)) * 0.2f;
    amount = amount > fovy ? amount : fovy;
    _90.sub_710079C384(sead::Mathf::clamp(amount, 10.0f, 90.0f), 0.0f);
    _90.sub_710079C3F8(_328);
    _32c.set(2);
}

void CameraEventMultiTalk::m45() {}

}  // namespace uking::action
