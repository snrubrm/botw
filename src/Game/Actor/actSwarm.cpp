#include "Game/Actor/actSwarm.h"
#include <basis/seadNew.h>
#include <math/seadMatrixCalcCommon.h>

namespace uking::act {

Swarm::Swarm(const CreateArg& arg) : Enemy(arg) {}

// NON_MATCHING: member types incomplete
Swarm::~Swarm() = default;

// NON_MATCHING: store schedule only: the original stores the units buffer pointer (_14d0) first, we merge it into
// the zeroing of _14d8 .. _14f0
ksys::act::BaseProc* Swarm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Swarm(arg);
}

void Swarm::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    Actor::setMtx(mtx, a2, a3);
    sead::Matrix34CalcCommon<f32>::inverse(_15b8, mMtx);
}

}  // namespace uking::act
