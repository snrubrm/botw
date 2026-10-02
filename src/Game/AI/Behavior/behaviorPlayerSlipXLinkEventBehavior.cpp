#include "Game/AI/Behavior/behaviorPlayerSlipXLinkEventBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

// NON_MATCHING: the original stores _48 after _50 (field types not known yet)
PlayerSlipXLinkEventBehavior::PlayerSlipXLinkEventBehavior(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

PlayerSlipXLinkEventBehavior::~PlayerSlipXLinkEventBehavior() = default;

bool PlayerSlipXLinkEventBehavior::m6(sead::Heap* heap) {
    return true;
}

void PlayerSlipXLinkEventBehavior::loadParams() {

}

void PlayerSlipXLinkEventBehavior::m8() {
    _48 = nullptr;
    _51 = false;
}

void PlayerSlipXLinkEventBehavior::m9() {
    sub_71012412E4(mActor, 27, 0.0f, false);
    sub_71012412E4(mActor, 28, 0.0f, false);
}

}  // namespace uking::behavior
