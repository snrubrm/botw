#include "Game/AI/Behavior/behaviorChangeCharacterStandingOnFlag.h"

namespace uking::behavior {

ChangeCharacterStandingOnFlag::ChangeCharacterStandingOnFlag(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ChangeCharacterStandingOnFlag::~ChangeCharacterStandingOnFlag() = default;

bool ChangeCharacterStandingOnFlag::m6(sead::Heap* heap) {
    return true;
}

void ChangeCharacterStandingOnFlag::m8() {}

void ChangeCharacterStandingOnFlag::m9() {}

void ChangeCharacterStandingOnFlag::loadParams() {
    getStaticParam(&mChangeScaleLimit_s, "ChangeScaleLimit");
    getStaticParam(&mSetValue_s, "SetValue");
}

}  // namespace uking::behavior
