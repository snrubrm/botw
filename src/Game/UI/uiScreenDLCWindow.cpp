#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/AOC/aocManager.h"

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

// NON_MATCHING: the original assigns the label inline (sead::SafeStringBase<char>::operator= is inline in the
// game's sead: it only copies mStringTop), so the original has no second SafeString and no call to it. Ours
// calls the out-of-line operator= (lib/sead declares it in the header and defines it in the .cpp), which adds
// the call and a 0x20-larger frame. The control flow, the branch structure and the vtable/string stores match.
// 0x7100a05cb4
void ScreenDLCWindow::sub_7100A05CB4(bool use_alt_animators) {
    _3870->StopAtMin();
    if (_3878)
        _3878->StopAtMin();
    _3890->setFlag10(false);
    _3898->setFlag10(false);

    eui::MessageString message;
    const u32 version = ksys::aoc::Manager::instance()->getVersion();
    sead::SafeString label;
    if (version >= 0x300)
        label = sead::SafeString("0031");
    else if (version >= 0x200)
        label = sead::SafeString("0030");
    else
        label = sead::SafeString("0032");
    getMessage(sUnk_7102486d38, label, &message);
    setWidgetString(mLayout, "T_Title_00", message);
    open(1);
    if (use_alt_animators) {
        mLayout->setOpenAnimator(_3860);
        mLayout->setCloseAnimator(_3868);
    } else {
        mLayout->setOpenAnimator(_3850);
        mLayout->setCloseAnimator(_3858);
    }
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
