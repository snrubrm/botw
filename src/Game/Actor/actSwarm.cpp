#include "Game/Actor/actSwarm.h"
#include <math/seadMatrixCalcCommon.h>

namespace uking::act {

// NON_MATCHING: member types incomplete
Swarm::~Swarm() = default;

void Swarm::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    Actor::setMtx(mtx, a2, a3);
    sead::Matrix34CalcCommon<f32>::inverse(_15b8, mMtx);
}

}  // namespace uking::act
