#include "Game/AI/Action/actionWaitForCloseFade.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

WaitForCloseFade::WaitForCloseFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForCloseFade::~WaitForCloseFade() = default;

bool WaitForCloseFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForCloseFade::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForCloseFade::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForCloseFade::loadParams_() {
    getDynamicParam(&mOrClosing_d, "OrClosing");
}

void WaitForCloseFade::calc_() {
    if (isFinished() || isFailed())
        return;
    if (*mOrClosing_d &&
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade)->isClosedOrClosing())
        setFinished();
    if (eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade)->isClosed())
        setFinished();
}

}  // namespace uking::action
