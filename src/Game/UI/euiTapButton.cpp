#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bf0324 / 0x7100bf0328
void TapButton::On() {}
void TapButton::Off() {}

// 0x7100bf032c
bool TapButton::ProcessDown() {
    switch (mState) {
    case kOff:
        StartDown();
        changeState(kStartDown);
        return false;
    case kStartOn:
        return false;
    case kStartOff:
        return false;
    case kOn:
        return false;
    case kStartDown:
        return true;
    case kDown:
        return true;
    case kCancel:
        return false;
    default:
        return true;
    }
}

// 0x7100bf039c
void TapButton::FinishDown() {
    changeState(kDown);
    changeState(kOff);
}

// 0x7100bf03d8
void TapButton::ForceOff() {
    ButtonBase::ForceOff();
    selectStateAnim(4)->StopAtMin();
}

}  // namespace eui
