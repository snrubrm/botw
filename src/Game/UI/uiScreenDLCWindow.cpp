#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// The message set of ScreenDLCWindow (a constant object in the original, 0x7102486d38, next to sResult).
static const sead::SafeString sUnk_7102486d38 = "LayoutMsg/DLCWindow_00";

s32 ScreenDLCWindow::sResult = 2;

void ScreenDLCWindow::m154() {
    eui::MessageString message_l;
    eui::MessageString message_r;
    getMessage(sUnk_7102486d38, "T_BtnL_00", &message_l);
    getMessage(sUnk_7102486d38, "T_BtnR_00", &message_r);
    setWidgetString(_3890->mLayout, "T_Btn_00", message_l);
    setWidgetString(_3898->mLayout, "T_Btn_00", message_r);
    _3870->Stop(1.0f);
    _3890->setFlag10(true);
    _3898->setFlag10(true);
    mButtonGroup->_38 |= 2;
    open(1);
    mLayout->setOpenAnimator(_3850);
    mLayout->setCloseAnimator(_3858);
    if (_3880)
        _3880->PlayAuto(1.0f);
}

// 0x7100a05f94
s32 ScreenDLCWindow::sub_7100A05F94() {
    const s32 result = sResult;
    sResult = 2;
    return result;
}

// 0x7100a060e0
void ScreenDLCWindow::m107(eui::AnimButton* button) {
    if (button->IsPlayDisableAnim()) {
        mButtonGroup->_38 |= 2;
        return;
    }
    switch (button->mTag) {
    case 89:
        sResult = 1;
        break;
    case 90:
        sResult = 0;
        break;
    }
    if (sResult)
        close(-1);
}

}  // namespace uking::ui
