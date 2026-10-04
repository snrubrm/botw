#include "Game/gameMaskController.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MaskController)

sead::Controller* MaskController::getController(ControllerIdx idx) {
    return mControllers(idx);
}

// NON_MATCHING: the original copies the SEAD_ENUM argument through three stack temporaries (stp w1, w1, [sp, #4] and a
// third copy at the end); ours only needs one.
void MaskController::sub_71008BCF44(ControllerIdx idx, bool on) {
    _2c |= 1u << idx;
    if (on)
        _28 |= 1u << idx;
    else
        _28 &= ~(1u << idx);
}

}  // namespace uking
