#include "KingSystem/System/UIGlue.h"
#include "Game/UI/euiUIController.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x71010a8454
ScreenMessageTips::ScreenMessageTips() : Screen() {}

ScreenMessageTips::~ScreenMessageTips() = default;

// 0x71010a87f0
// NON_MATCHING: the original keeps the "type 18 while 19 is current" case as its own branch that jumps to the shared
// store; clang makes it a select
bool ScreenMessageTips::sub_71010A87F0(s32 type) {
    if ((type | 1) != 19)
        return false;

    if (type == 18 && _3a8 == 19)
        type = 19;
    if (_3a8 == type)
        _3ac = type;
    else
        type = _3ac;
    return type != 29;
}

// 0x71010a8840
void ScreenMessageTips::m93(sead::Heap*) {
    _318.sub_71010A7CA4(sub_7100BEAFB0("Pa_Tips_00"));
    _318.sub_71010A7EDC(sub_7100BEAFB0("Pa_TipsAmiibo_00"), mLayout->createAnimatorAuto("Type", false));
    _300 = sub_7100BEAFB0("Pa_ABtn_00");
    if (_300)
        _308 = _300->tryCreateAnimatorAutoWithWarning("DecideOut", true);
}

// 0x71010a88e4
// NON_MATCHING: the original tests the {5, 8, 21} set with a bit mask before the sound switch; ours compares directly
void ScreenMessageTips::m94() {
    switch (_3a8) {
    case 5:
        ksys::ui::sub_7100EDC458();
        break;
    case 8:
        ksys::ui::sub_7100EDC470();
        break;
    case 21:
        ksys::ui::sub_7100EDC488();
        break;
    default:
        break;
    }
    if (!isOpened())
        return;
    if (_300 && !_310) {
        _300->sub_7100BDDE7C(false, 0, true);
        _310 = true;
    }
    if (!isTrigMaybe(_3b0) && _3a8 != _3ac)
        return;
    if (_3a8 == 5 || _3a8 == 8 || _3a8 == 21) {
        if (isTrigMaybe(0x400))
            ksys::ui::sub_7100EDC4D0();
    } else if (_3a8 == 17) {
        if (isTrigMaybe(0x200))
            ksys::ui::sub_7100EDC4E8();
    }
    if (_300 && _308) {
        _300->sub_7100BDDE7C(false, 1, true);
        _308->PlayAuto(1.0f);
    }
    close(-1);
}

// 0x71010a8a9c
void ScreenMessageTips::doDraw_(const eui::DrawInfoEx::RenderBufferInfo* info) {
    Screen::doDraw_(info);
}

// 0x71010a8aa0
void ScreenMessageTips::m98() {
    if (_300) {
        if (_308)
            _308->StopAtMin();
        _300->startAnimCloseImpl_(false, true);
    }
    _310 = false;
}

// 0x71010a8af0
void ScreenMessageTips::m100() {
    _3a8 = 29;
}

// 0x71010a8afc
const char* ScreenMessageTips::getLayoutName_() const {
    return "MessageTips_00";
}

}  // namespace uking::ui
