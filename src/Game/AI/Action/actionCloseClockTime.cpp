#include "Game/AI/Action/actionCloseClockTime.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiScreen.h"

namespace uking::action {

CloseClockTime::CloseClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseClockTime::~CloseClockTime() = default;

bool CloseClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseClockTime::loadParams_() {}

bool CloseClockTime::oneShot_() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Time))
        screen->close(-1);
    return true;
}

}  // namespace uking::action
