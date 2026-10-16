#include "Game/Actor/Behavior/behaviorSwarmPattern.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPattern::SwarmPattern(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPattern::~SwarmPattern() = default;

bool SwarmPattern::init_(sead::Heap* heap) {
    return SwarmPatternBase::init_(heap);
}

void SwarmPattern::calc() {
    SwarmPatternBase::calc();
}

void SwarmPattern::enter() {
    SwarmPatternBase::enter();
}

void SwarmPattern::leave() {
    SwarmPatternBase::leave();
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
