// TU 0x71008bbda4-0x71008bbf38 (per-frame controller update helpers; next to the MaskController TU,
// which starts at 0x71008bbf3c).
#include "Game/gameMaskController.h"

namespace uking {

sead::Controller* MaskController::getControllerSafe(ControllerIdx idx) {
    auto* instance = MaskController::instance();
    if (!instance)
        return nullptr;
    return instance->getController(idx);
}

}  // namespace uking
