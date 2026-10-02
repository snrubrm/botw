#include "Game/AI/Behavior/behaviorClearFadeInCreate.h"

namespace uking::behavior {

ClearFadeInCreate::ClearFadeInCreate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ClearFadeInCreate::~ClearFadeInCreate() = default;

bool ClearFadeInCreate::m6(sead::Heap* heap) {
    return true;
}

void ClearFadeInCreate::m9() {}

}  // namespace uking::behavior
