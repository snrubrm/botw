#include "Game/AI/Query/queryKeyInputCheck.h"
#include <controller/seadController.h>
#include <controller/seadControllerWrapper.h>
#include <evfl/Query.h>
#include "Game/gameMaskController.h"

namespace uking::query {

KeyInputCheck::KeyInputCheck(const InitArg& arg) : ksys::act::ai::Query(arg) {}

KeyInputCheck::~KeyInputCheck() = default;

// NON_MATCHING: same control flow as the original, but the original reads the hold mask at +8 of both controller
// objects (sead::ControllerBase::getHoldMask() is at +0x114 in our build) and loads `_28` / `_2c` before the mask.
// The original falls back to a virtual call of its own doQuery slot when the MaskController (or its controller) is
// missing.
int KeyInputCheck::doQuery() {
    auto* mask = uking::MaskController::instance();
    bool no_controller = false;
    if (_28) {
        sead::Controller* controller = nullptr;
        if (mask)
            controller = mask->getController(uking::MaskController::ControllerIdx(2));
        if (controller) {
            if (controller->getHoldMask() & _28)
                return true;
        } else {
            no_controller = true;
        }
    }
    if (_2c) {
        if (mask) {
            if (mask->sub_71008BCA40()->getHoldMask() & _2c)
                return true;
            if (!no_controller)
                return false;
        }
        return doQuery();
    }
    if (!no_controller)
        return false;
    return doQuery();
}

void KeyInputCheck::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "ValidInput");
    switch (*mValidInput) {
    case 0:
        _28 = 0x623b;
        _2c = 0;
        break;
    case 1:
        _28 = 0;
        _2c = 1;
        break;
    case 2:
        _28 = 1;
        _2c = 0;
        break;
    case 3:
        _28 = 1;
        _2c = 1;
        break;
    default:
        _28 = 0xfffffff;
        _2c = 0;
        break;
    }
}

void KeyInputCheck::loadParams() {
    getDynamicParam(&mValidInput, "ValidInput");
}

}  // namespace uking::query
