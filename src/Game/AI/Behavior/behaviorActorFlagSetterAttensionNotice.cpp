#include "Game/AI/Behavior/behaviorActorFlagSetterAttensionNotice.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: case order / block layout (the original tests 2, 1, then 0, and uses a select for
// the first flag in case 2)
void ActorFlagSetterAttensionNotice::m8() {
    using Flag = ksys::act::Actor::ActorFlag2;
    switch (*mMode_s) {
    case 0:
        mActor->getActorFlags2().change(Flag::_1000000, *mSetValue_s);
        break;
    case 2:
        mActor->getActorFlags2().change(Flag::_1000000, *mSetValue_s);
        [[fallthrough]];
    case 1:
        mActor->getActorFlags2().change(Flag::_2000000, *mSetValue_s);
        break;
    }
}

}  // namespace uking::behavior
