#include "Game/AI/Action/actionWaitForFrame.h"
#include <controller/seadController.h>
#include "Game/gameMaskController.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

WaitForFrame::WaitForFrame(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForFrame::~WaitForFrame() = default;

bool WaitForFrame::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForFrame::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = *mFrame_d;
    if (*mValidInput_s == 1)
        _34 = 0xff062ff;
}

void WaitForFrame::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForFrame::loadParams_() {
    getStaticParam(&mValidInput_s, "ValidInput");
    getDynamicParam(&mFrame_d, "Frame");
}

void WaitForFrame::calc_() {
    // NON_MATCHING: the original tests a mask at +8 of the object returned by MaskController::getController
    // (not sead::Controller's pad hold bits at +0x114); the element type of its controller array is unknown
    if (isFinished() || isFailed())
        return;
    ksys::Timer::update(&_30, -1.0f);
    if (auto* mask_controller = MaskController::instance()) {
        if (auto* controller = mask_controller->getController(MaskController::ControllerIdx::_2)) {
            if (_34 && controller->isHold(_34))
                _30 = 0.0f;
        }
    }
    if (_30 <= 0.0f) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
