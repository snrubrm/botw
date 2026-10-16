#include "Game/Actor/Behavior/behaviorPlayerSlipXLinkEventBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

PlayerSlipXLinkEventBehavior::PlayerSlipXLinkEventBehavior(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

PlayerSlipXLinkEventBehavior::~PlayerSlipXLinkEventBehavior() = default;

bool PlayerSlipXLinkEventBehavior::init_(sead::Heap* heap) {
    return true;
}

void PlayerSlipXLinkEventBehavior::loadParams() {

}

void PlayerSlipXLinkEventBehavior::enter() {
    _48 = 0;
    _4c = 0;
    _51 = false;
}

void PlayerSlipXLinkEventBehavior::leave() {
    sub_71012412E4(mActor, 27, 0.0f, false);
    sub_71012412E4(mActor, 28, 0.0f, false);
}

}  // namespace uking::behavior
