#include "Game/AI/Behavior/behaviorActorFlagSetterAttensionNotice.h"

namespace uking::behavior {

ActorFlagSetterAttensionNotice::ActorFlagSetterAttensionNotice(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ActorFlagSetterAttensionNotice::~ActorFlagSetterAttensionNotice() = default;

bool ActorFlagSetterAttensionNotice::m6(sead::Heap* heap) {
    return true;
}

void ActorFlagSetterAttensionNotice::m7() {}

void ActorFlagSetterAttensionNotice::m9() {}

void ActorFlagSetterAttensionNotice::loadParams() {
    getStaticParam(&mMode_s, "Mode");
    getStaticParam(&mSetValue_s, "SetValue");
}

}  // namespace uking::behavior
