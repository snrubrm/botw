#include "Game/Actor/actSwarm.h"
#include <random/seadGlobalRandom.h>

namespace uking::act {

void Swarm::Unit::sub_71002DAA98() {
    if (!(_b8 & 2))
        _b8 = (_b8 & ~0xc) | 8;
}

void Swarm::Unit::sub_71002DAA78() {
    if (_b8 & 2) {
        _b8 = (_b8 & ~0xe) | 4;
        _bc = 0;
    }
}

}  // namespace uking::act

void Unk_71023d0e08::m8() {
    uking::act::Swarm::Unit::m8();
}

Unk_71023d0e08::Unk_71023d0e08()
    : _e0(30.0f), _e4(0.0f), _e8(0.0f), _ec(1.0f), _f0(0.0f), _f4(0) {}

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

void Unk_71023d0e08::m6() {
    uking::act::Swarm::Unit::m6();
    _e0 = 30.0f;
    sub_71002DB2EC();
    sub_71002DAE8C();
    sub_71002DAEDC();
}
