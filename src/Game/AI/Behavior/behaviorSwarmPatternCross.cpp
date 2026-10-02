#include "Game/AI/Behavior/behaviorSwarmPatternCross.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternCross::SwarmPatternCross(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternCross::~SwarmPatternCross() = default;

bool SwarmPatternCross::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternCross::m7() {
    SwarmPattern::m7();
}

void SwarmPatternCross::m9() {
    SwarmPattern::m9();
}

void SwarmPatternCross::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mWidth_s, "Width");
}

void SwarmPatternCross::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
