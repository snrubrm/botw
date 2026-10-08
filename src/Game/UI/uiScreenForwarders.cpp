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

// 0x7100a51790: app-tag router bound to ScreenShopInfo::_3768.
u32 ScreenShopInfo::sub_7100A51790(const sead::MessageSet<char16>::TagInfo* tag,
                                   sead::WBufferedSafeString* out) {
    if (tag->type != 8) {
        if (tag->type != 7)
            return 0;
        return sub_7100AA4E60(&_3788, out);
    }
    return sub_7100AA5140(&_3788, out);
}

// 0x710010a5068
eui::TagProcessor* ScreenMainDungeon::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a0ff60
void ScreenMainHardMode::close(s32 option) {
    Screen::close(option);
}

eui::TagProcessor* ScreenMessageDialog::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

}  // namespace uking::ui
