#include "Game/Actor/Behavior/behaviorFootstepSilencer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::behavior {

FootstepSilencer::FootstepSilencer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

FootstepSilencer::~FootstepSilencer() = default;

bool FootstepSilencer::init_(sead::Heap* heap) {
    return true;
}

void FootstepSilencer::calc() {}

void FootstepSilencer::enter() {
    if (auto* xlink = mActor->getXLink()) {
        if (auto* settings = xlink->_a0)
            settings->_1c.set(0x10);
    }
}

void FootstepSilencer::leave() {
    if (auto* xlink = mActor->getXLink()) {
        if (auto* settings = xlink->_a0)
            settings->_1c.reset(0x10);
    }
}

void FootstepSilencer::loadParams() {

}

}  // namespace uking::behavior
