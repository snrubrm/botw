#include "Game/UI/uiUtils.h"
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
// 0x7100a238c8
u32 ScreenMessageGet::sub_7100A238C8(const sead::MessageSet<char16>::TagInfo* tag,
                                     sead::WBufferedSafeString* out) {
    if (tag->type != 8) {
        if (tag->type != 7)
            return 0;
        return sub_7100AA4E60(&_36f0, out);
    }
    return sub_7100AA5140(&_36f0, out);
}

u32 ScreenShopInfo::sub_7100A51790(const sead::MessageSet<char16>::TagInfo* tag,
                                   sead::WBufferedSafeString* out) {
    if (tag->type != 8) {
        if (tag->type != 7)
            return 0;
        return sub_7100AA4E60(&_3788, out);
    }
    return sub_7100AA5140(&_3788, out);
}


// 0x7100a0ff60
void ScreenMainHardMode::close(s32 option) {
    Screen::close(option);
}

eui::TagProcessor* ScreenMessageDialog::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x7100a5e0b8
void ScreenStaffRoll::m73(f32 value) {
    _270 = value;
    open(1);
}

// 0x7100a5e1b0
void ScreenStaffRoll::m76() {
    _270 = 0;
    close(-1);
}

// 0x7100a5e58c
void ScreenStaffRoll::m101() {
    sub_7100AA86EC(1, true);
}

// 0x7100a58c5c
void ScreenStaffRollDLC::m73(f32 value) {
    _270 = value;
    open(1);
}

// 0x7100a58c70
void ScreenStaffRollDLC::m74(f32 progress) {
    sub_7100A58508(progress, _270);
    if (_270 < progress)
        m76();
}

// 0x7100a58cc8
void ScreenStaffRollDLC::m76() {
    _270 = 0;
    close(-1);
}

// 0x7100a5e42c: the original's whole body is a tail call to the same class's 0x7100a5dce8.
void ScreenStaffRoll::sub_7100A5E42C(f32 time) {
    sub_7100A5DCE8(time);
}

}  // namespace uking::ui
