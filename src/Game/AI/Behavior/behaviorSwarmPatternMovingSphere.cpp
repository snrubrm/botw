#include "Game/AI/Behavior/behaviorSwarmPatternMovingSphere.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternMovingSphere::SwarmPatternMovingSphere(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPatternMovingSphere::~SwarmPatternMovingSphere() = default;

bool SwarmPatternMovingSphere::m6(sead::Heap* heap) {
    return SwarmPatternBase::m6(heap);
}

void SwarmPatternMovingSphere::loadParams() {
    SwarmPatternBase::loadParams();
    getStaticParam(&mUseSubActorNum_s, "UseSubActorNum");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mCycleSpeed_s, "CycleSpeed");
}

void SwarmPatternMovingSphere::m14(f32 value, act::Swarm* swarm) {
    swarm->_1628 = 2;
    swarm->_162c = 2;
    swarm->_1620 = value;
}

}  // namespace uking::behavior
