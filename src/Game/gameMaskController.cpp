#include "Game/gameMaskController.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MaskController)

sead::Controller* MaskController::getController(ControllerIdx idx) {
    return mControllers(idx);
}

sead::ControllerWrapperBase* MaskController::sub_71008BCA40() {
    return &_40;
}

}  // namespace uking
