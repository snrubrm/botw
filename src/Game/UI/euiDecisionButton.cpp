#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd8c34
DecisionButton::DecisionButton(const DecisionButton& other, LayoutEx* layout, sead::Heap* heap) {
    CloneImpl_(other, layout, heap);
    mFlags |= 0x20;
}

// 0x7100bd8c98
bool DecisionButton::ProcessOn() {
    switch (mState) {
    case kOff:
        StartOn();
        changeState(kStartOn);
        return true;
    case kStartOn:
        return true;
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        return true;
    case kOn:
        return true;
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
