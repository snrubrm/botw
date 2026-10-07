#include "Game/AI/Action/actionForceMarkPosition.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::action {

ForceMarkPosition::ForceMarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceMarkPosition::~ForceMarkPosition() = default;

bool ForceMarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ForceMarkPosition::oneShot_() {
    auto* pin = ui::UiSubsys1::instance()->sub_71009644E8(*mPinColorIdx_d);
    if (pin)
        pin->sub_7100951388(false);
    return true;
}

void ForceMarkPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
}

}  // namespace uking::action
