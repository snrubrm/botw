#include "Game/gameMaskController.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MaskController)

sead::Controller* MaskController::getController(ControllerIdx idx) {
    return mControllers(idx);
}

}  // namespace uking
