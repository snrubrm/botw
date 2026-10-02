#include "Game/AI/Behavior/behaviorViewLastAttackerPos.h"

namespace uking::behavior {

ViewLastAttackerPos::ViewLastAttackerPos(const InitArg& arg) : NeckControl(arg) {}

ViewLastAttackerPos::~ViewLastAttackerPos() = default;

bool ViewLastAttackerPos::m6(sead::Heap* heap) {
    return NeckControl::m6(heap);
}

void ViewLastAttackerPos::m7() {
    NeckControl::m7();
}

void ViewLastAttackerPos::m8() {
    NeckControl::m8();
}

void ViewLastAttackerPos::m9() {
    NeckControl::m9();
}

void ViewLastAttackerPos::loadParams() {
    NeckControl::loadParams();
}

}  // namespace uking::behavior
