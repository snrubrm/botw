#include "Game/UI/uiScreens.h"

// Overrides that only forward to ScreenBase's version (the original has a 4-byte `b` for each of them).
namespace uking::ui {

// 0x7100a24360
eui::TagProcessor* ScreenMessageGet::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a26004
eui::TagProcessor* ScreenMessageTipsPauseMenu::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a26c28
eui::TagProcessor* ScreenMessageTipsRunTime::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a2ce64
eui::TagProcessor* ScreenPauseMenuInfo::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a351f4
eui::TagProcessor* ScreenPauseMenu::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a51bac
eui::TagProcessor* ScreenShopInfo::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x710010a5068
eui::TagProcessor* ScreenMainDungeon::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a0ff60
void ScreenMainHardMode::close(s32 option) {
    Screen::close(option);
}

}  // namespace uking::ui
