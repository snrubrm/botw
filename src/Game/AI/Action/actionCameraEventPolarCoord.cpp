#include "Game/AI/Action/actionCameraEventPolarCoord.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraEventPolarCoord::CameraEventPolarCoord(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventPolarCoord::m43() {
    m47();
    _8c = 0;
    _90 = false;
    _91 = true;
}

// NON_MATCHING: the original computes the _7c0 link address before calling m59 (C++14 operand order of
// the overloaded BaseProcLink assignment); the final `rate <= 0` checks are jump-threaded in ours.
void CameraEventPolarCoord::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;

    if (!_90) {
        _90 = m48();
        if (_90) {
            const act::Unk_7100922700 cur(camera->_860._0._0 - camera->_860._0._c);
            sead::Vector3f at = sead::Vector3f::zero;
            m55(&at);
            const f32 elevation = angleStuff(m51());
            const f32 azimuth = angleStuff(m52());
            const act::Unk_7100922700 target(m53(), elevation, azimuth);
            target.sub_7100923254();
            _4c = at;
            _58 = camera->_860._0._c - _4c;
            _64 = target._4;
            _68 = angleStuff(cur._4 - _64);
            _6c = target._8;
            _70 = angleStuff(cur._8 - _6c);
            _74 = target._0;
            _78 = cur._0 - _74;
            _7c = m54();
            _80 = camera->_860._0._24 - _7c;
            _84 = 0;
            _88 = camera->_860._0._28;
            if (m57())
                camera->sub_71007929E0();
        }

        if (!_90) {
            m50();
            if (auto* cam = getCamera())
                cam->_860._7c0[cam->_860._81a] = *m59();
            const s32 max = sub_7100922088();
            if (_8c < max)
                ++_8c;
            if (_8c >= max)
                setFailed();
            return;
        }
    }

    const bool immediate = !_91 && m57();
    m49();
    const f32 rate = m58();

    if (immediate) {
        act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        m55(&_4c);
        camera->_860._0._c = _4c;
        _64 = angleStuff(m51());
        polar._4 = _64;
        polar._4 = angleStuff(sub_7100924CAC(polar._4));
        _6c = angleStuff(m52());
        polar._8 = _6c;
        _74 = m53();
        polar._0 = sub_7100924D40(_74);
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
        _7c = m54();
        camera->_860._0._24 = sub_7100924D50(_7c);
        _84 = 0;
        camera->_860._0._28 = 0;
        _58 = sead::Vector3f::zero;
        _68 = angleStuff(0);
        _70 = angleStuff(0);
        _78 = 0;
        _80 = 0;
        _88 = 0;
        _91 = false;
        camera->sub_71007929E0();
        setFinished();
    } else {
        act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        const f32 t = sub_7100791E44(0.6f);
        sead::Vector3f at = sead::Vector3f::zero;
        m55(&at);
        _4c += (at - _4c) * t;
        camera->_860._0._c = _4c + _58 * rate;

        _64 = angleStuff(angleStuff(t * angleStuff(angleStuff(m51()) - _64)) + _64);
        polar._4 = angleStuff(angleStuff(rate * _68) + _64);
        polar._4 = angleStuff(sub_7100924CAC(polar._4));
        _6c = angleStuff(angleStuff(t * angleStuff(angleStuff(m52()) - _6c)) + _6c);
        polar._8 = angleStuff(angleStuff(rate * _70) + _6c);
        _74 += t * (m53() - _74);
        polar._0 = sub_7100924D40(_74 + rate * _78);
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
        _7c += t * (m54() - _7c);
        camera->_860._0._24 = sub_7100924D50(_7c + rate * _80);
        _84 += t * (0.0f - _84);
        camera->_860._0._28 = _84 + t * _88;
    }

    if (rate <= 0.0f && _91)
        _91 = false;
    if (rate <= 0.0f)
        setFinished();

    m50();
    if (auto* cam = getCamera())
        cam->_860._7c0[cam->_860._81a] = *m59();
}

const ksys::act::BaseProcLink* CameraEventPolarCoord::m59() {
    return &ksys::act::sUnk_71026505e0;
}

void CameraEventPolarCoord::m47() {}

bool CameraEventPolarCoord::m48() {
    return true;
}

void CameraEventPolarCoord::m49() {}

void CameraEventPolarCoord::m50() {}

float CameraEventPolarCoord::m51() {
    return 0.0f;
}

float CameraEventPolarCoord::m52() {
    return 0.0f;
}

float CameraEventPolarCoord::m53() {
    return 10.0f;
}

float CameraEventPolarCoord::m54() {
    return sead::Mathf::piHalf();
}

void CameraEventPolarCoord::m55(sead::Vector3f* out) {}

void CameraEventPolarCoord::m56(act::Unk_7100922700* out) {}

bool CameraEventPolarCoord::m57() {
    return false;
}

float CameraEventPolarCoord::m58() {
    return 1.0f;
}

}  // namespace uking::action
