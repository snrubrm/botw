#include "Game/Actor/Behavior/behaviorSwarmPatternHoldHomePos.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternHoldHomePos::SwarmPatternHoldHomePos(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPatternHoldHomePos::~SwarmPatternHoldHomePos() = default;

bool SwarmPatternHoldHomePos::init_(sead::Heap* heap) {
    return SwarmPatternBase::init_(heap);
}

void SwarmPatternHoldHomePos::calc() {
    SwarmPatternBase::calc();
}

void SwarmPatternHoldHomePos::enter() {
    SwarmPatternBase::enter();
}

void SwarmPatternHoldHomePos::leave() {
    SwarmPatternBase::leave();
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
