#include "Game/Actor/actSwarm.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

// The two concrete swarm unit variants; Swarm::prepareInit_ allocates one of them per unit.

Unk_71023d0d08::Unk_71023d0d08() = default;

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71023d0d08::~Unk_71023d0d08() {
    ;
}

Unk_71023d0e08::Unk_71023d0e08()
    : _e0(30.0f), _e4(0.0f), _e8(0.0f), _ec(1.0f), _f0(0.0f), _f4(0) {}

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71023d0e08::~Unk_71023d0e08() {
    ;
}

bool Unk_71023d0e08::m4(uking::act::Swarm* owner, sead::Heap* heap) {
    return uking::act::Swarm::Unit::m4(owner, heap);
}

void Unk_71023d0e08::m6() {
    uking::act::Swarm::Unit::m6();
    _e0 = 30.0f;
    sub_71002DB2EC();
    sub_71002DAE8C();
    sub_71002DAEDC();
}

void Unk_71023d0e08::m8() {
    uking::act::Swarm::Unit::m8();
}

void Unk_71023d0e08::sub_71002DAE8C() {
    _f0 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi2();
}

void Unk_71023d0e08::sub_71002DAEDC() {
    _d4.reset(sead::GlobalRandom::instance()->getF32Range(150.0f, 450.0f));
    _e8 = sead::GlobalRandom::instance()->getF32Range(-0.5f * _e0, 0.5f * _e0);
    _ec = sead::GlobalRandom::instance()->getF32Range(0.15f, 0.25f);
    _f4 = 0;
}

void Unk_71023d0e08::sub_71002DB2EC() {
    _e4 = sead::Mathf::deg2rad(sead::Mathf::clamp(
        60.0f - _e0 + sead::GlobalRandom::instance()->getF32Range(-5.0f, 5.0f), 3.0f, 60.0f));
}
