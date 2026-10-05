#include "Game/AI/Action/actionKillUIScreenAction.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

KillUIScreenAction::KillUIScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillUIScreenAction::~KillUIScreenAction() = default;

bool KillUIScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillUIScreenAction::loadParams_() {
    getDynamicParam(&mScreenName_d, "ScreenName");
}

bool KillUIScreenAction::oneShot_() {
    const s32 index = ui::getScreenIdxByName(mScreenName_d.cstr());
    if (index != 99) {
        if (auto* screen = eui::ScreenMgr::instance()->getScreen(index))
            screen->close(-4);
    }
    return true;
}

}  // namespace uking::action
