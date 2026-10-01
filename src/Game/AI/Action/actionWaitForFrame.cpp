#include "Game/AI/Action/actionWaitForFrame.h"

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
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
