#include "Game/AI/Behavior/behaviorBreakIceBlockAtAttackHit.h"

namespace uking::behavior {

BreakIceBlockAtAttackHit::BreakIceBlockAtAttackHit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

BreakIceBlockAtAttackHit::~BreakIceBlockAtAttackHit() = default;

bool BreakIceBlockAtAttackHit::m6(sead::Heap* heap) {
    return true;
}

void BreakIceBlockAtAttackHit::m8() {}

void BreakIceBlockAtAttackHit::m9() {}

void BreakIceBlockAtAttackHit::loadParams() {

}

}  // namespace uking::behavior
