#include "Game/AI/Action/actionWaitCloseItemDownloadDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

WaitCloseItemDownloadDemo::WaitCloseItemDownloadDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaitCloseItemDownloadDemo::~WaitCloseItemDownloadDemo() = default;

bool WaitCloseItemDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitCloseItemDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A9ED74();
}

void WaitCloseItemDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitCloseItemDownloadDemo::loadParams_() {}

void WaitCloseItemDownloadDemo::calc_() {
    if (isFinished() || isFailed() || ui::sub_7100A9EBEC())
        return;
    setFinished();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
