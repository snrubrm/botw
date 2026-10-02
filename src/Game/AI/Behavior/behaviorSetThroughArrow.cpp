#include "Game/AI/Behavior/behaviorSetThroughArrow.h"

namespace uking::behavior {

// NON_MATCHING: the object at 0x58 is not declared yet (placeholder bytes)
SetThroughArrow::SetThroughArrow(const InitArg& arg) : SetDamageCallback(arg) {}

SetThroughArrow::~SetThroughArrow() = default;

bool SetThroughArrow::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetThroughArrow::m7() {
    SetDamageCallback::m7();
}

void SetThroughArrow::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetThroughArrow::m14() {
    return &_30;
}

}  // namespace uking::behavior
