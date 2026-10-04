#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/System/Timer.h"
#include <prim/seadScopedLock.h>
#include <math/seadMathCalcCommon.h>

// Initialized writable parameters present in the original scene TU. Names are address placeholders;
// no larger parameter-object layout is assumed from the compiler's merged static block.
static f32 sUnk_710243bfec = 0.73f;
static f32 sUnk_710243bff0 = 1.25f;
static f32 sUnk_710243c00c = 1.0f;
static f32 sUnk_710243c010 = 0.0f;
static f32 sUnk_710243c014 = 0.15f;
static f32 sUnk_710243c018 = 0.3f;

void GameSceneSubsys12::init(sead::Heap* heap) {
    _318.sub_710065D8E4(heap, true);
}

bool GameSceneSubsys12::x() const {
    return _a78.isBitOn(0);
}

Unk_710243be90* GameSceneSubsys12::sub_7100663278(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (auto* entry = _318.sub_710065E2B0(proc))
        return entry;

    bool has_carrier = _300.hasProc() && _310;
    if (!has_carrier) {
        _a78.setBitOff(3);
        if (auto* carrier = sub_7100662C4C()) {
            _300.acquire(carrier, false);
            sub_7100662EF0(carrier);
        }
        has_carrier = _300.hasProc() && _310;
    }
    if (has_carrier) {
        if (auto* entry = _310->sub_710065E2B0(proc))
            return entry;
    }
    proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    return nullptr;
}

bool GameSceneSubsys12::sub_7100663364(sead::Matrix34f* out) {
    if (!_300.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    // The original calls acquireActor but discards its result after the hasProc check.
    ksys::act::acquireActor(&_300, &accessor);
    *out = accessor.getActorMtx();
    return true;
}

s32 GameSceneSubsys12::sub_710066358C() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065F044() : 0;
}

bool GameSceneSubsys12::sub_71006652C8() const {
    return _300.hasProc() && !_a78.isBitOn(0);
}

s32 GameSceneSubsys12::sub_7100664D24() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _318.sub_710065F044();
}

s32 GameSceneSubsys12::sub_7100664D64() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065F07C() : 0;
}

void GameSceneSubsys12::sub_7100664F00(const sead::Matrix34f& matrix) {
    _d8 = matrix;
    if (_a78.isBitOn(2))
        ksys::Timer::update(&_270, 1.0f);
}

bool GameSceneSubsys12::sub_7100664F30() const {
    return _a78.isBitOn(2);
}

void GameSceneSubsys12::sub_7100664F3C(const sead::Matrix34f& matrix) {
    _108 = matrix;
}

void GameSceneSubsys12::sub_7100664F64(const sead::Matrix34f& matrix) {
    _138 = matrix;
}

void GameSceneSubsys12::sub_7100665304() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    _270 = 0.0f;
    _a78.setBitOn(2);
    if (_300.hasProc() && _310)
        _310->sub_710065F9AC();
}

ksys::act::BaseProcLink* GameSceneSubsys12::sub_7100664BC8(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (_300.hasProc() && _310)
        return _310->sub_710065F80C(index);
    return nullptr;
}

ksys::act::BaseProcLink* GameSceneSubsys12::sub_7100664DBC(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _318.sub_710065F80C(index);
}

f32 GameSceneSubsys12::sub_7100664ACC(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065FA28(proc, _270) : 0.0f;
}

void GameSceneSubsys12::sub_7100665360() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    _d4 = 0;
    _a78.setBitOff(0);
    _a78.setBitOff(2);
    _270 = 0.0f;
    sub_7100664484(4, _310);
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_300, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

// NON_MATCHING: the original count clamp contains an int-float-int round trip, and copy stores differ.
void GameSceneSubsys12::sub_7100664CC0(sead::Vector3f* out, s32 count, s32 index) {
    if (out) {
        const s32 row = sead::Mathi::clamp(count - 1, 0, 4);
        *out = _a98[row][index];
    }
}

// NON_MATCHING: scene parameter statics are folded; original loads them from its merged static block.
f32 GameSceneSubsys12::sub_7100664B3C(ActorContextStuff* context, f32 scale) {
    if (_300.hasProc() && _310 == context && _a78.isBitOn(0)) {
        const f32 doubled_scale = scale + scale;
        const f32 limited_scale = sead::Mathf::min(sUnk_710243bfec, doubled_scale * sUnk_710243bff0);
        return _d0 * (limited_scale / doubled_scale - 1.0f) + 1.0f;
    }
    return 1.0f;
}

// NON_MATCHING: integer clamp, folded scene parameters and store scheduling differ.
void GameSceneSubsys12::sub_7100664C30(sead::Vector3f* out, s32 count, s32 index) {
    if (out) {
        const s32 row = sead::Mathi::clamp(count - 1, 0, 4);
        out->x = sUnk_710243c00c * _a98[row][index].x - sUnk_710243c010;
        out->y = sUnk_710243c00c * _a98[row][index].y - sUnk_710243c014;
        out->z = sUnk_710243c00c * _a98[row][index].z - sUnk_710243c018;
    }
}
