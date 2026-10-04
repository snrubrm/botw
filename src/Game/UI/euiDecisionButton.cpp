#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd8c34
DecisionButton::DecisionButton(const DecisionButton& other, LayoutEx* layout, sead::Heap* heap) {
    CloneImpl_(other, layout, heap);
    mFlags |= 0x20;
}

// NON_MATCHING: the original tests the kOff state last (cbnz) instead of first (cbz)
// 0x7100bd8c98
bool DecisionButton::ProcessOn() {
    bool handled = true;
    switch (mState) {
    case kOff:
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        break;
    case kCancel:
        handled = false;
        break;
    default:
        break;
    }
    return handled;
}

// 0x7100bd8d08
bool DecisionButton::ProcessOff() {
    if (mState == kStartOn) {
        StartOff();
        changeState(kStartOff);
    } else if (mState == kOn) {
        StartOff();
        changeState(kStartOff);
    }
    return true;
}

// 0x7100bd8d60
void DecisionButton::FinishDown() {
    changeState(kDown);
}

}  // namespace eui
