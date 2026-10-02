#include "Game/AI/Behavior/behaviorSandwormTeraUpdateTypeSetter.h"

namespace uking::behavior {

SandwormTeraUpdateTypeSetter::SandwormTeraUpdateTypeSetter(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SandwormTeraUpdateTypeSetter::~SandwormTeraUpdateTypeSetter() = default;

bool SandwormTeraUpdateTypeSetter::m6(sead::Heap* heap) {
    return true;
}

void SandwormTeraUpdateTypeSetter::m7() {}

void SandwormTeraUpdateTypeSetter::loadParams() {
    getStaticParam(&mUpdateType_s, "UpdateType");
}

}  // namespace uking::behavior
