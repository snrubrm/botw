#include "Game/AI/Action/actionCameraHorse.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

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
        _262 = false;
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

}  // namespace uking::action
