#include "Game/AI/Behavior/behaviorSwarmPatternDoubleRing.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternDoubleRing::SwarmPatternDoubleRing(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternDoubleRing::~SwarmPatternDoubleRing() = default;

bool SwarmPatternDoubleRing::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternDoubleRing::m7() {
    SwarmPattern::m7();
}

void SwarmPatternDoubleRing::m9() {
    SwarmPattern::m9();
}

void SwarmPatternDoubleRing::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mCenterOffsetHalf_s, "CenterOffsetHalf");
}

void SwarmPatternDoubleRing::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
