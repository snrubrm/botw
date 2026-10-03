#include "Game/AI/Action/actionWaitUntilMapOpenDemoEnd.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

WaitUntilMapOpenDemoEnd::WaitUntilMapOpenDemoEnd(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitUntilMapOpenDemoEnd::~WaitUntilMapOpenDemoEnd() = default;

bool WaitUntilMapOpenDemoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitUntilMapOpenDemoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitUntilMapOpenDemoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitUntilMapOpenDemoEnd::loadParams_() {}

void WaitUntilMapOpenDemoEnd::calc_() {
    if (isFinished() || isFailed() || !ui::sub_7100A9A3F8())
        return;
    setFinished();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
