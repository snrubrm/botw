#include "Game/AI/Action/actionOpenClockTime.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiScreen.h"

namespace uking::action {

OpenClockTime::OpenClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenClockTime::~OpenClockTime() = default;

bool OpenClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenClockTime::loadParams_() {}

bool OpenClockTime::oneShot_() {
    ui::createAndLoadScreenIfNeededImpl(ui::ScreenId::Time, nullptr);
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Time))
        screen->open(1);
    return true;
}

}  // namespace uking::action
