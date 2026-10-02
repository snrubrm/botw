#include "Game/AI/Action/actionWaitForKeyInput.h"
#include <controller/seadController.h>
#include <controller/seadControllerWrapperBase.h>
#include "Game/gameMaskController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WaitForKeyInput::WaitForKeyInput(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForKeyInput::~WaitForKeyInput() = default;

bool WaitForKeyInput::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForKeyInput::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mValidInput_d) {
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

void WaitForKeyInput::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForKeyInput::loadParams_() {
    getDynamicParam(&mValidInput_d, "ValidInput");
}

void WaitForKeyInput::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* mask = MaskController::instance();
    if (_28 != 0) {
        sead::Controller* controller;
        if (!mask || !(controller = mask->getController(MaskController::ControllerIdx(2))))
            setFailed();
        else if (controller->isTrig(_28))
            setFinished();
    }
    if (_2c != 0) {
        if (!mask)
            setFailed();
        else if (mask->sub_71008BCA40()->isTrig(_2c))
            setFinished();
    }

    if (isFinished() || isFailed())
        mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
