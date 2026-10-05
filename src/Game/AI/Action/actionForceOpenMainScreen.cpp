#include "Game/AI/Action/actionForceOpenMainScreen.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

ForceOpenMainScreen::ForceOpenMainScreen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOpenMainScreen::~ForceOpenMainScreen() = default;

bool ForceOpenMainScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceOpenMainScreen::loadParams_() {}

bool ForceOpenMainScreen::oneShot_() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreen)) {
        if (!screen->isOpening() && !screen->isOpened())
            screen->open(1);
    }
    return true;
}

}  // namespace uking::action
