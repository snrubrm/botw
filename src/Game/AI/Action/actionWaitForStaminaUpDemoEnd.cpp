#include "Game/AI/Action/actionWaitForStaminaUpDemoEnd.h"
#include "Game/AI/aiUnk_710073BB28.h"

namespace uking::action {

WaitForStaminaUpDemoEnd::WaitForStaminaUpDemoEnd(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForStaminaUpDemoEnd::~WaitForStaminaUpDemoEnd() = default;

bool WaitForStaminaUpDemoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForStaminaUpDemoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForStaminaUpDemoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForStaminaUpDemoEnd::loadParams_() {}

void WaitForStaminaUpDemoEnd::calc_() {
    if (isFinished())
        return;
    if (isFailed())
        return;
    if (sub_710073BB54())
        setFinished();
}

}  // namespace uking::action
