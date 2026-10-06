#include "Game/AI/Action/actionIchigekiHeartUiOpen.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

IchigekiHeartUiOpen::IchigekiHeartUiOpen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiOpen::~IchigekiHeartUiOpen() = default;

bool IchigekiHeartUiOpen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiOpen::loadParams_() {}

bool IchigekiHeartUiOpen::oneShot_() {
    auto* screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
    if (screen && screen->isOpened())
        return true;
    if (!screen) {
        ui::createAndLoadScreenIfNeededImpl(ui::ScreenId::MainScreenHeartIchigekiDLC, nullptr);
        screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
    }
    if (screen)
        screen->open(1);
    return true;
}

}  // namespace uking::action
