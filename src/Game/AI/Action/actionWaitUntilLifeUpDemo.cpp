#include "Game/AI/Action/actionWaitUntilLifeUpDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

WaitUntilLifeUpDemo::WaitUntilLifeUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitUntilLifeUpDemo::~WaitUntilLifeUpDemo() = default;

bool WaitUntilLifeUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitUntilLifeUpDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitUntilLifeUpDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitUntilLifeUpDemo::loadParams_() {}

void WaitUntilLifeUpDemo::calc_() {
    if (isFinished() || isFailed() || ui::sub_7100A94AC8() || ui::sub_7100A94E08())
        return;
    setFinished();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
