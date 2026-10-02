#include "Game/AI/Behavior/behaviorSwarmPatternHoldHomePos.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternHoldHomePos::SwarmPatternHoldHomePos(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPatternHoldHomePos::~SwarmPatternHoldHomePos() = default;

bool SwarmPatternHoldHomePos::m6(sead::Heap* heap) {
    return SwarmPatternBase::m6(heap);
}

void SwarmPatternHoldHomePos::m7() {
    SwarmPatternBase::m7();
}

void SwarmPatternHoldHomePos::m8() {
    SwarmPatternBase::m8();
}

void SwarmPatternHoldHomePos::m9() {
    SwarmPatternBase::m9();
}

void SwarmPatternHoldHomePos::loadParams() {
    SwarmPatternBase::loadParams();
    getStaticParam(&mRotateType_s, "RotateType");
}

void SwarmPatternHoldHomePos::m14(f32 value, act::Swarm* swarm) {
    SwarmPatternBase::m14(value, swarm);
    swarm->_1628 = 1;
    const s32 num = *mRotateType_s;
    swarm->_162c = (num >= 1 && num <= 8) ? num : 1;
}

}  // namespace uking::behavior
