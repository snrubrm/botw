#include "Game/AI/Behavior/behaviorSwarmPattern.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPattern::SwarmPattern(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPattern::~SwarmPattern() = default;

bool SwarmPattern::m6(sead::Heap* heap) {
    return SwarmPatternBase::m6(heap);
}

void SwarmPattern::m7() {
    SwarmPatternBase::m7();
}

void SwarmPattern::m8() {
    SwarmPatternBase::m8();
}

void SwarmPattern::m9() {
    SwarmPatternBase::m9();
}

void SwarmPattern::loadParams() {
    SwarmPatternBase::loadParams();
    getStaticParam(&mNoiseMax_s, "NoiseMax");
}

void SwarmPattern::m14(f32 value, act::Swarm* swarm) {
    swarm->_1628 = 3;
    swarm->_1620 = value;
    swarm->_1624 = *mNoiseMax_s;
}

}  // namespace uking::behavior
