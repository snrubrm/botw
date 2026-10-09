#include "Game/AI/Action/actionCameraMagneCatch.h"

#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"

namespace uking::action {

// NON_MATCHING: native pre-construction array zeroing is not emitted by the typed array.
CameraMagneCatch::CameraMagneCatch(const InitArg& arg) : CameraLockOnBase(arg), _338(this), _388(this), _3d8(this) {}

// NON_MATCHING: out-of-line callback destructors remain to preserve their existing native identities.
CameraMagneCatch::~CameraMagneCatch() = default;

// NON_MATCHING: callback context stores and pointer-array register allocation differ.
bool CameraMagneCatch::m42(sead::Heap* heap) {
    _1c0.bind(this, &CameraMagneCatch::sub_7100775B78);
    _1e0.bind(this, &CameraMagneCatch::sub_7100775B80);
    _200.bind(this, &CameraMagneCatch::sub_7100775B88);
    {
        const Unk_7102457ac0::InitArg arg(this, &_1c0);
        // called through a pointer in the original (not devirtualised)
        (&_220[0])->m4(&arg);
    }
    {
        const Unk_7102457ac0::InitArg arg(this, &_1e0);
        // called through a pointer in the original (not devirtualised)
        (&_220[1])->m4(&arg);
    }
    {
        const Unk_7102457ac0::InitArg arg(this, &_200);
        // called through a pointer in the original (not devirtualised)
        (&_220[2])->m4(&arg);
    }
    _310.pushBack(&_220[0]);
    _310.pushBack(&_220[1]);
    _310.pushBack(&_220[2]);
    _428.pushBack(&_338);
    _428.pushBack(&_388);
    _428.pushBack(&_3d8);
    return true;
}

// NON_MATCHING: the native first-state search is unrolled separately from the current-state search.
int CameraMagneCatch::sub_71007761FC() {
    auto* states = m47();
    if (!states)
        return -1;
    auto* checkers = m49();
    if (!checkers)
        return -1;
    const int current = _f8;
    if (current != -1 && _454 > 90.0f && current >= 1) {
        for (int i = 0; i < current; ++i) {
            auto* state = states->at(i);
            if (!state)
                continue;
            auto* checker = checkers->at(i);
            if (!checker)
                continue;
            state->m5();
            if (checker->sub_7100786E14(state->_10) != 2)
                return i;
        }
    }
    for (int i = current == -1 ? 0 : current; i < 3; ++i) {
        auto* state = states->at(i);
        if (!state)
            continue;
        auto* checker = checkers->at(i);
        if (!checker)
            continue;
        state->m5();
        if (checker->sub_7100786E14(state->_10) != 2)
            return i;
    }
    return -1;
}

int CameraMagneCatch::m59() {
    const int state = sub_71007761FC();
    if (state == _f8)
        sead::Mathf::chase(&_454, 3000.0f, ksys::VFR::instance()->getDeltaFrame());
    else
        _454 = 0.0f;
    return state;
}

sead::PtrArray<Unk_7102457a80>* CameraMagneCatch::m47() {
    return &_310;
}

const sead::PtrArray<Unk_7102457a80>* CameraMagneCatch::m48() {
    return &_310;
}

sead::PtrArray<Unk_7102457b00>* CameraMagneCatch::m49() {
    return &_428;
}

const sead::PtrArray<Unk_7102457b00>* CameraMagneCatch::m50() {
    return &_428;
}

void CameraMagneCatch::m43() {
    _454 = 0.0f;
}

bool CameraMagneCatch::m51() {
    auto* camera = getCamera();
    if (!camera)
        return false;
    _64 = camera->_860._4cc;
    _70 = camera->_860._4cc;
    _7c = camera->_860._4cc;
    return true;
}

// NON_MATCHING: angular chase and polar field scheduling differ.
void CameraMagneCatch::m52() {
    const f32 rate = sub_7100791E44(0.15f);
    _a0._c._4 = angleStuff(angleStuff(rate * angleStuff(_88._c._4 - _a0._c._4)) + _a0._c._4);
    _a0._c._0 += rate * (_88._c._0 - _a0._c._0);
    const f32 difference = angleStuff(_88._c._8 - _a0._c._8);
    const f32 longitude_rate = sub_7100791E44(sub_7100922330());
    const f32 step = angleStuff(difference * longitude_rate);
    f32 offset = angleStuff(0);
    const f32 magnitude = difference > 0 ? difference : -difference;
    if (magnitude > 5.0f) {
        offset = difference;
        sead::Mathf::chase(&offset, 0.0f, 5.0f);
    }
    const f32 step_magnitude = step > 0 ? step : -step;
    const f32 offset_magnitude = offset > 0 ? offset : -offset;
    const f32 adjustment = offset_magnitude > step_magnitude ? offset : step;
    _a0._c._8 = angleStuff(adjustment + _a0._c._8);
    _a0._0 = _a0._c.sub_7100923254();
}

// NON_MATCHING: callback state loads and angle scheduling differ.
void CameraMagneCatch::m46(act::Unk_7100922700* polar, bool reset) {
    f32 longitude = angleStuff(0);
    sub_71007866C4(&longitude);
    if (reset) {
        _450 = longitude;
    } else {
        const f32 rate = sub_7100791E44(0.1f);
        _450 = angleStuff(angleStuff(rate * angleStuff(longitude - _450)) + _450);
    }
    longitude = angleStuff(sub_7100922530(_a0._c._8) + _450);
    const f32 longitude_rate = sub_7100791E44(*mLngCus_s);
    f32 longitude_delta = angleStuff(longitude_rate * angleStuff(longitude - polar->_8));
    longitude_delta = angleStuff(longitude_delta * _c4);
    longitude_delta = angleStuff(longitude_delta * (_b8 * -0.5f + 1.0f));
    polar->_8 = angleStuff(longitude_delta + polar->_8);
    f32 latitude = angleStuff(0);
    const auto* states = m47();
    if (sub_7100786CC0() && states) {
        const auto* state = states->at(_f4);
        const act::Unk_7100922700 direction(state->_10._0 - state->_10._c);
        latitude = direction._4;
    }
    const f32 latitude_rate = sub_7100791E44(*mLatCus_s);
    f32 latitude_delta = angleStuff(latitude_rate * angleStuff(latitude - polar->_4));
    latitude_delta = angleStuff(latitude_delta * _c4);
    polar->_4 = angleStuff(latitude_delta + polar->_4);
}

void CameraMagneCatch::sub_7100775B78(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 1.0f);
}

void CameraMagneCatch::sub_7100775B80(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 0.5f);
}

void CameraMagneCatch::sub_7100775B88(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 0.0f);
}

float CameraMagneCatch::m44() {
    return sub_7100922318();
}

float CameraMagneCatch::m45() {
    return sub_7100922324();
}

bool CameraMagneCatch::m55(f32* out0, f32* out1) {
    *out0 = 1.0f;
    *out1 = 0.0f;
    if (!sub_7100786CC0())
        return false;
    f32 value = 1.0f;
    if (_f4 == 1)
        value = 0.5f;
    if (_f4 == 2)
        value = 0.0f;
    *out0 = value;
    *out1 = 0.0f;
    return true;
}

// NON_MATCHING: float stack slots and paired zero stores differ.
void CameraMagneCatch::sub_7100775F84(act::Unk_71009214b8* out, f32 rate) {
    auto* camera = getCamera();
    if (!camera)
        return;
    *out = camera->_860._0;
    f32 longitude = 0.0f;
    sub_7100786974(&longitude);
    longitude = angleStuff(longitude + sub_7100922530(_a0._c._8));
    const f32 current = angleStuff(-_88._c._4);
    f32 latitude = *mLatOffsetNear_s + (*mLatOffsetFar_s - *mLatOffsetNear_s) * _b8;
    if (angleStuff(current) > angleStuff(latitude))
        latitude += angleStuff(current - latitude);
    angleStuff(latitude);
    latitude = angleStuff(current + angleStuff(angleStuff(latitude) - current) * rate);
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    if (latitude < min)
        latitude = min;
    else if (latitude > max)
        latitude = max;
    const f32 clamped_latitude = angleStuff(latitude);
    sub_7100786A44(out, &clamped_latitude, &longitude);
}

}  // namespace uking::action
