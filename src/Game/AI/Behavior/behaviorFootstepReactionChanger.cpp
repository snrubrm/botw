#include "Game/AI/Behavior/behaviorFootstepReactionChanger.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

// Original enum ownership and source namespace are unknown; declarations only.
const char* sub_7100E367C0(s32 index);
const char* sub_7100E36B54(s32 index);

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

// NON_MATCHING: bounded lookup iteration and string comparison scheduling differ.
void FootstepReactionChanger::loadParams() {
    getStaticParam(&mChangeDuration_s, "ChangeDuration");
    getStaticParam(&mReactionType_s, "ReactionType");
    getStaticParam(&mScaleType_s, "ScaleType");

    s32 reaction = 0;
    for (; reaction < 29; ++reaction) {
        if (mReactionType_s == sead::SafeString(sub_7100E367C0(reaction)))
            break;
    }
    _50 = reaction < 29 ? reaction : 0;

    s32 scale = 0;
    for (; scale < 5; ++scale) {
        if (mScaleType_s == sead::SafeString(sub_7100E36B54(scale)))
            break;
    }
    _54 = scale < 5 ? scale : 0;
}

// NON_MATCHING: reaction/scale fields are loaded before the duration parameter.
void FootstepReactionChanger::m8() {
    mActor->getXLink()->_a0->sub_7101236520(_50, _54, *mChangeDuration_s);
}

void FootstepReactionChanger::m9() {
    mActor->getXLink()->_a0->sub_71012370A8();
}

}  // namespace uking::behavior
