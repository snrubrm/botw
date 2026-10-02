#include "Game/AI/Behavior/behaviorHorseSetCollarBehavior.h"

namespace uking::behavior {

HorseSetCollarBehavior::HorseSetCollarBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseSetCollarBehavior::~HorseSetCollarBehavior() = default;

bool HorseSetCollarBehavior::m6(sead::Heap* heap) {
    return true;
}

void HorseSetCollarBehavior::m7() {}

void HorseSetCollarBehavior::m9() {}

void HorseSetCollarBehavior::loadParams() {
    getStaticParam(&mHorseShoeFrame_s, "HorseShoeFrame");
}

}  // namespace uking::behavior
