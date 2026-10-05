#include "Game/AI/Action/actionIchigekiHeartUiClose.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

IchigekiHeartUiClose::IchigekiHeartUiClose(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiClose::~IchigekiHeartUiClose() = default;

bool IchigekiHeartUiClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiClose::loadParams_() {}

bool IchigekiHeartUiClose::oneShot_() {
    auto* screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
    if (screen)
        screen->close(-1);
    return true;
}

}  // namespace uking::action
