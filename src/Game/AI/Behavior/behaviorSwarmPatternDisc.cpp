#include "Game/AI/Behavior/behaviorSwarmPatternDisc.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternDisc::SwarmPatternDisc(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternDisc::~SwarmPatternDisc() = default;

bool SwarmPatternDisc::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternDisc::m7() {
    SwarmPattern::m7();
}

void SwarmPatternDisc::m9() {
    SwarmPattern::m9();
}

void SwarmPatternDisc::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mRadius_s, "Radius");
}

void SwarmPatternDisc::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
