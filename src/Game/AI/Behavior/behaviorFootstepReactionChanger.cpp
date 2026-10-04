#include "Game/AI/Behavior/behaviorFootstepReactionChanger.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::behavior {

FootstepReactionChanger::FootstepReactionChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
FootstepReactionChanger::~FootstepReactionChanger() {
    ;
}

bool FootstepReactionChanger::m6(sead::Heap* heap) {
    return true;
}

void FootstepReactionChanger::m7() {}

// NON_MATCHING: reaction/scale fields are loaded before the duration parameter.
void FootstepReactionChanger::m8() {
    mActor->getXLink()->_a0->sub_7101236520(_50, _54, *mChangeDuration_s);
}

void FootstepReactionChanger::m9() {
    mActor->getXLink()->_a0->sub_71012370A8();
}

}  // namespace uking::behavior
