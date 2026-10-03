#include "Game/AI/Action/actionMarkPosition.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::action {

MarkPosition::MarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MarkPosition::~MarkPosition() = default;

bool MarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPosition::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
}

// NON_MATCHING: the original stores x with a single `str` and y / z with one `stp`; ours pairs x / y
// and stores z separately.
bool MarkPosition::oneShot_() {
    const sead::Vector3f pos{*mPositionX_d, *mPositionY_d, *mPositionZ_d};
    ui::UiSubsys1::instance()->sub_71009645D0(&pos);
    return true;
}

}  // namespace uking::action
