#include "Game/AI/Behavior/behaviorFootstepSilencer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::behavior {

FootstepSilencer::FootstepSilencer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

FootstepSilencer::~FootstepSilencer() = default;

bool FootstepSilencer::m6(sead::Heap* heap) {
    return true;
}

void FootstepSilencer::m7() {}

void FootstepSilencer::m8() {
    if (auto* xlink = mActor->getXLink()) {
        if (auto* settings = xlink->_a0)
            settings->_1c.set(0x10);
    }
}

void FootstepSilencer::m9() {
    if (auto* xlink = mActor->getXLink()) {
        if (auto* settings = xlink->_a0)
            settings->_1c.reset(0x10);
    }
}

void FootstepSilencer::loadParams() {

}

}  // namespace uking::behavior
