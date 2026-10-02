#include "Game/AI/Behavior/behaviorOffOcculutionCulling.h"

namespace uking::behavior {

OffOcculutionCulling::OffOcculutionCulling(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OffOcculutionCulling::~OffOcculutionCulling() = default;

bool OffOcculutionCulling::m6(sead::Heap* heap) {
    return true;
}

void OffOcculutionCulling::loadParams() {

}

}  // namespace uking::behavior
