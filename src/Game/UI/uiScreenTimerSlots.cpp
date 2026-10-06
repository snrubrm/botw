#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x7100a25ff4
void ScreenMessageTipsPauseMenu::m93(sead::Heap*) {
    _3614.init(6.0f);
}

// 0x7100a26008
void ScreenMessageTipsPauseMenu::m94() {
    if (isOpened()) {
        if (_3614.updateAndCheckEnded())
            close(-1);
        if (!_362c && _3614.getProgress() >= 0.6666667f) {
            switch (_3610) {
            case 0:
                ksys::gdt::setFlag_GuideP_ChallengePoint(true, false);
                break;
            case 1:
                ksys::gdt::setFlag_GuideP_VisitMark(true, false);
                break;
            }
            _362c = 1;
        }
    }
}

// 0x7100a260b8
void ScreenMessageTipsPauseMenu::m98() {
    _3614.reset();
    _362c = 0;
}

// 0x7100a0fec8
void ScreenMainHardMode::open(s32 option) {
    if (isOpening() || isOpened())
        return;
    if (!_3628) {
        _3610.init(0.5f);
        _3628 = 1;
    }
    _3610.update();
    if (_3610.checkEnded()) {
        _3628 = 0;
        Screen::open(option);
    }
}

}  // namespace uking::ui
