#include "Game/AI/Behavior/behaviorSwarmPatternBeeAttack.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternBeeAttack::SwarmPatternBeeAttack(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternBeeAttack::~SwarmPatternBeeAttack() = default;

bool SwarmPatternBeeAttack::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternBeeAttack::m8() {
    SwarmPattern::m8();
}

void SwarmPatternBeeAttack::m9() {
    SwarmPattern::m9();
}

void SwarmPatternBeeAttack::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mDepth_s, "Depth");
    getStaticParam(&mWidth_s, "Width");
}

void SwarmPatternBeeAttack::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 7;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
