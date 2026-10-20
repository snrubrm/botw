#include <basis/seadTypes.h>
#include "Game/UI/uiScreens.h"

// Small helpers around TU-level state of the app screens (AppCamera, AppMapDungeon, AppPictureBook, AppTool). The
// variables are unnamed in the binary; `sUnk_<address>` placeholders.
namespace uking::ui {

// 0x71025de180 (used by the ScreenAppMapDungeon functions): flag bits
u16 sUnk_71025de180;
// 0x71025de182
KSYS_VISIBILITY_HIDDEN u8 sUnk_71025de182;
// 0x71025eb5b8 / 0x71025eb5b4: mode set by sub_71009F8420
s32 sUnk_71025eb5b8;
u8 sUnk_71025eb5b4;
// 0x71025ec540 / 0x71025ec549 (ScreenAppTool)
AppToolState sUnk_71025ec540;
bool sUnk_71025ec548;
bool sUnk_71025ec549;
u8 sUnk_71025ec54a;

sead::PtrArray<Unk_71009cb0c8> sUnk_71025eb5c0;
sead::PtrArray<Unk_71009cb0c8*> sUnk_71025dc5e0;
s32 sUnk_71025dc57c;
bool sUnk_71025dc580;

// 0x7102483490 (.data, initial value 6)
s32 sUnk_7102483490 = 6;

namespace {
// TU-local state of the AppPictureBook screen (0x71025eb850)
bool sUnk_71025eb850;
}  // namespace

// 0x71009fc4a0
s32 ScreenAppSystemWindow::sub_71009FC4A0() {
    const s32 value = sUnk_7102483490;
    sUnk_7102483490 = 6;
    return value;
}

namespace {
// 0x7102483480
sead::SafeString sAppSystemWindowMsg = "LayoutMsg/AppSystemWindow_00";
}  // namespace

// 0x71009fcb7c
void ScreenAppSystemWindow::sub_71009FCB7C(s32 index, s32 msg_id, bool on) {
    if (_3638[index])
        _3638[index]->setFlag10(on);
    if (msg_id == -1 || !on || !mLayout || !_3620[index])
        return;
    sead::FormatFixedSafeString<64> label("%04d", msg_id);
    eui::MessageString message;
    getMessage(sAppSystemWindowMsg, label, &message);
    setWidgetString(_3620[index], "T_Btn_00", message);
}

// 0x71009fff58
void AppToolState::sub_71009FFF58() {
    _0 = -1;
    _4 = false;
    _5 = false;
}

// 0x71009e2e94
bool sub_71009E2E94() {
    return sUnk_71025de180 & 1;
}

// 0x71009e7ce8
void sub_71009E7CE8(s32) {
    sUnk_71025de180 |= 3;
}

// 0x71009f8420
void sub_71009F8420(s32 a1) {
    sUnk_71025eb5b8 = a1;
    sUnk_71025eb5b4 = 0;
    if (a1 == 1)
        sUnk_71025eb850 = true;
}

// 0x71009f8450
bool sub_71009F8450() {
    return !sUnk_71025eb850;
}

// 0x71009fd6c0
void sub_71009FD6C0() {
    if (sUnk_71025ec540._0 != -1)
        sUnk_71025ec549 = 1;
}

}  // namespace uking::ui
