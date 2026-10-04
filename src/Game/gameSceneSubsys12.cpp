#include "Game/gameSceneSubsys12.h"
#include "KingSystem/System/Timer.h"
#include <prim/seadScopedLock.h>

void GameSceneSubsys12::init(sead::Heap* heap) {
    _318.sub_710065D8E4(heap, true);
}

bool GameSceneSubsys12::x() const {
    return _a78.isBitOn(0);
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
